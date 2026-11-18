// Calls decompiled ROCK_NEO.EXE functions natively, with the retail executable image loaded
// from the owner's disc into the RAM mapped at 0x80000000 (nothing from the disc is stored in
// the repository).
//
// Usage: harness [path/to/ROCK_NEO.EXE]   (default: disc/extracted/ROCK_NEO.EXE in the repo)
#include "port_stubs.h"
#include "psx_mem.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef PORT_DEFAULT_EXE
#define PORT_DEFAULT_EXE "disc/extracted/ROCK_NEO.EXE"
#endif

// Decompiled game functions under test (src/rock_neo.exe).
void Sce_flag_on(uint32_t flag);                                       // scene.c
uint32_t Sce_flag_test(uint32_t flag);                                 // scene.c
int32_t func_8001E83C(int16_t x0, int16_t y0, int16_t x1, int16_t y1); // scene.c
uint32_t func_8003AC24(uint32_t key);                                  // code_8003AC24.c
int16_t func_8001DDC0(uint8_t *p);                                     // scene.c (file static)
void Vsync_handler(void);                                              // main.c
void func_800131FC(void);                                              // main.c
void func_80017684(void *src, void *dst, int32_t count);               // asm_fastmem (native C)
void func_800177CC(void *start, void *end);                            // asm_fastmem (native C)

// Retail data, reached through the absolute symbols from gen_link.py.
extern int32_t D_800891F0[4];
extern uint32_t D_8013A004;
extern uint8_t Sce_flag[];
extern uint32_t D_80098158;   // main.c defines it ($gp tentative definition): placed data
extern uint32_t D_80080894[]; // retail data: the main thread's state dispatch table

// PsyQ routines run from the retail image (psyq_emulated.c).
int rsin(int a);
int rcos(int a);
int ratan2(int y, int x);
long SquareRoot0(long a);
int catan(int t);

// GTE checks built from the game's macros (gte_case.c).
typedef struct
{
    int16_t m[3][3];
    int16_t pad;
    int32_t t[3];
} GTE_CASE_MATRIX;
typedef struct
{
    int16_t vx, vy, vz, pad;
} GTE_CASE_SVECTOR;
void gte_case_rtv0(GTE_CASE_MATRIX *mat, GTE_CASE_SVECTOR *v, int32_t *out);
uint32_t gte_case_rtps(GTE_CASE_MATRIX *mat, GTE_CASE_SVECTOR *v, int32_t h, int32_t ofx,
                       int32_t ofy, int32_t *sz);
int32_t gte_case_nclip(uint32_t a, uint32_t b, uint32_t c);

static int failures;

#define CHECK(cond, ...)                                                                           \
    do                                                                                             \
    {                                                                                              \
        int ok_ = (cond);                                                                          \
        printf("%s ", ok_ ? "ok  " : "FAIL");                                                      \
        printf(__VA_ARGS__);                                                                       \
        printf("\n");                                                                              \
        failures += !ok_;                                                                          \
    } while (0)

static uint32_t file_word(const char *path, uint32_t addr)
{
    // The same word read straight from the file, to compare with what the symbol sees.
    FILE *f = fopen(path, "rb");
    uint8_t hdr[0x20], b[4];
    uint32_t t_addr;

    if (f == NULL)
    {
        return 0xDEADBEEF;
    }
    if (fread(hdr, 1, sizeof(hdr), f) != sizeof(hdr))
    {
        fclose(f);
        return 0xDEADBEEF;
    }
    t_addr = hdr[0x18] | (hdr[0x19] << 8) | (hdr[0x1A] << 16) | ((uint32_t)hdr[0x1B] << 24);
    fseek(f, 0x800 + (long)(addr - t_addr), SEEK_SET);
    if (fread(b, 1, 4, f) != 4)
    {
        fclose(f);
        return 0xDEADBEEF;
    }
    fclose(f);
    return b[0] | (b[1] << 8) | (b[2] << 16) | ((uint32_t)b[3] << 24);
}

static void test_flags(void)
{
    printf("-- Sce_flag_on / Sce_flag_test (scene flags in retail BSS)\n");
    CHECK((uintptr_t)Sce_flag == 0x800BE378, "Sce_flag at %p (retail 0x800BE378)",
          (void *)Sce_flag);
    CHECK(Sce_flag_test(0x123) == 0, "flag 0x123 starts clear");
    Sce_flag_on(0x123);
    CHECK(Sce_flag_test(0x123) == 1, "flag 0x123 set");
    CHECK(Sce_flag_test(0x122) == 0 && Sce_flag_test(0x124) == 0, "neighbours still clear");
    CHECK(*(volatile uint8_t *)0x800BE39C == (0x80 >> 3), "byte 0x24 of the table = 0x%02X",
          *(volatile uint8_t *)0x800BE39C);
}

static void test_fastmem(void)
{
    uint32_t *a = (uint32_t *)0x801F0000, *b = (uint32_t *)0x801F0100;

    printf("-- hand-written copy routines (port/runtime/asm_native.c)\n");
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    b[3] = 0x77;
    func_80017684(a, b, 3);
    CHECK(b[0] == 1 && b[1] == 2 && b[2] == 3 && b[3] == 0x77, "word copy of 3 words");
    func_800177CC(&b[0], &b[2]);
    CHECK(b[0] == 0 && b[1] == 0 && b[2] == 0 && b[3] == 0x77, "zero fill, end included");
}

static int near(int32_t a, int32_t b)
{
    return a - b >= -1 && a - b <= 1;
}

static void test_retail_data(const char *exe)
{
    int i;
    int32_t e, s, w, n;

    printf("-- func_8001E83C (angle from two points; retail table D_800891F0 + catan)\n");
    for (i = 0; i < 4; i++)
    {
        uint32_t want = file_word(exe, 0x800891F0 + 4 * i);
        CHECK((uint32_t)D_800891F0[i] == want, "D_800891F0[%d] = 0x%X (file: 0x%X)", i,
              (uint32_t)D_800891F0[i], want);
    }
    e = func_8001E83C(0, 0, 100, 0);
    s = func_8001E83C(0, 0, 0, 100);
    w = func_8001E83C(0, 0, -100, 0);
    n = func_8001E83C(0, 0, 0, -100);
    printf("     east 0x%X, south 0x%X, west 0x%X, north 0x%X, diagonal 0x%X\n", e, s, w, n,
           func_8001E83C(0, 0, 100, 100));
    // PsyQ's catan (run from the retail image) is a CORDIC approximation: an angle can be one
    // unit off the exact value (catan(1.0) is 0x1FF, not 0x200).
    CHECK(near(((s - e) & 0xFFF), 0x400) || near(((e - s) & 0xFFF), 0x400),
          "east and south are a quarter turn apart (within a unit)");
    CHECK(near((w - e) & 0xFFF, 0x800) || near(((w - e) & 0xFFF) - 1, 0x800),
          "east and west are half a turn apart (within two units)");
    CHECK(near((n - s) & 0xFFF, 0x800), "north and south are half a turn apart (within a unit)");
}

static void test_literal_alias(void)
{
    uint32_t *tbl = (uint32_t *)0x8013A000; // the stage HED area (disc.md, "Load addresses")

    printf("-- func_8003AC24 (key lookup: symbol D_8013A004 and literal 0x8013A000 alias)\n");
    memset(tbl, 0, 0x40);
    tbl[0] = 0x11;
    tbl[1] = 0xAA;
    tbl[2] = 0x22;
    tbl[3] = 0xBB;
    CHECK(&D_8013A004 == (uint32_t *)0x8013A004, "&D_8013A004 = %p", (void *)&D_8013A004);
    CHECK(func_8003AC24(0x11) == 0xAA, "key 0x11 -> 0x%X", func_8003AC24(0x11));
    CHECK(func_8003AC24(0x22) == 0xBB, "key 0x22 -> 0x%X", func_8003AC24(0x22));
    CHECK(func_8003AC24(0x33) == 0, "key 0x33 -> 0x%X", func_8003AC24(0x33));
}

static void test_gte(void)
{
    GTE_CASE_MATRIX m;
    GTE_CASE_SVECTOR v;
    int32_t out[3], sz;
    uint32_t sxy;
    int16_t sx, sy;
    double ex, ey;

    printf("-- GTE through the game's macros (inline MIPS interpreted)\n");
    memset(&m, 0, sizeof(m));
    m.m[0][0] = m.m[1][1] = m.m[2][2] = 0x1000;
    m.t[0]                            = 10;
    m.t[1]                            = 20;
    m.t[2]                            = 300;
    v.vx                              = 100;
    v.vy                              = -200;
    v.vz                              = 300;
    v.pad                             = 0;
    gte_case_rtv0(&m, &v, out);
    CHECK(out[0] == 110 && out[1] == -180 && out[2] == 600, "rtv0 identity: %d %d %d", out[0],
          out[1], out[2]);

    // 90 degrees about Z: x' = -y, y' = x
    memset(&m, 0, sizeof(m));
    m.m[0][1] = -0x1000;
    m.m[1][0] = 0x1000;
    m.m[2][2] = 0x1000;
    gte_case_rtv0(&m, &v, out);
    CHECK(out[0] == 200 && out[1] == 100 && out[2] == 300, "rtv0 rotate: %d %d %d", out[0], out[1],
          out[2]);

    memset(&m, 0, sizeof(m));
    m.m[0][0] = m.m[1][1] = m.m[2][2] = 0x1000;
    m.t[2]                            = 1000;
    sxy                               = gte_case_rtps(&m, &v, 256, 160 << 16, 120 << 16, &sz);
    sx                                = (int16_t)(sxy & 0xFFFF);
    sy                                = (int16_t)(sxy >> 16);
    ex                                = 160 + 100.0 * 256 / 1300;
    ey                                = 120 - 200.0 * 256 / 1300;
    CHECK(sz == 1300 && fabs(sx - ex) <= 1 && fabs(sy - ey) <= 1,
          "rtps: sx %d sy %d sz %d (expected about %.1f %.1f 1300)", sx, sy, sz, ex, ey);

    CHECK(gte_case_nclip(0 | (0 << 16), 10 | (0 << 16), 0 | (10 << 16)) == 100,
          "nclip clockwise = %d", gte_case_nclip(0, 10, 10 << 16));
}

static void test_placement(void)
{
    uint32_t (*lookup)(uint32_t) = (uint32_t (*)(uint32_t))0x8003AC24;
    uint8_t bytes[2]             = {0x34, 0x12};
    uint32_t *tbl                = (uint32_t *)0x8013A000;

    printf("-- retail-address placement (gen_link.py, stub table)\n");
    CHECK((uintptr_t)&Sce_flag_on == 0x8001DA8C, "&Sce_flag_on = %p (retail 0x8001DA8C)",
          (void *)&Sce_flag_on);
    CHECK((uintptr_t)&Vsync_handler == 0x800123FC, "&Vsync_handler = %p (retail 0x800123FC)",
          (void *)&Vsync_handler);
    CHECK((uintptr_t)&D_80098158 == 0x80098158, "C-defined D_80098158 at %p", (void *)&D_80098158);
    CHECK(port_stub_find(D_80080894[0]) != NULL, "retail table D_80080894[0] = 0x%08X is %s",
          D_80080894[0],
          port_stub_find(D_80080894[0]) ? port_stub_find(D_80080894[0])->name : "unknown");
    CHECK(port_stub_find((uint32_t)(uintptr_t)&func_800131FC) != NULL &&
              port_stub_find((uint32_t)(uintptr_t)&func_800131FC)->missing == 0,
          "func_800131FC has native code behind its retail address");
    memset(tbl, 0, 0x10);
    tbl[0] = 0x11;
    tbl[1] = 0xAA;
    CHECK(lookup(0x11) == 0xAA, "call through the literal retail address 0x8003AC24");
    *(volatile uint16_t *)0x80098198 = 0;
    CHECK(func_8001DDC0(bytes) == 0x1234 && *(volatile uint16_t *)0x80098198 == 0x1234,
          "file static D_80098198 (scene.c) lives at its retail address: 0x%04X",
          *(volatile uint16_t *)0x80098198);
}

static void test_emulated(void)
{
    printf("-- PsyQ routines run from the retail image (MIPS interpreter)\n");
    CHECK(rsin(0) == 0 && rsin(0x400) == 0x1000 && rsin(-0x400) == -0x1000, "rsin: %d %d %d",
          rsin(0), rsin(0x400), rsin(-0x400));
    CHECK(rcos(0) == 0x1000 && rcos(0x800) == -0x1000, "rcos: %d %d", rcos(0), rcos(0x800));
    CHECK(ratan2(0x1000, 0x1000) == 0x200, "ratan2(1, 1) = 0x%X", ratan2(0x1000, 0x1000));
    // PsyQ's square root truncates through a table: 10000 gives 99 (the table entry for
    // 10000 >> 6 is 6394, and 6394 << 6 >> 12 = 99), as on the console.
    CHECK(SquareRoot0(10000) == 99 && SquareRoot0(0) == 0, "SquareRoot0(10000) = %ld (PsyQ: 99)",
          SquareRoot0(10000));
    // PsyQ's catan is 12 CORDIC steps over its table (D_80092B64), which leaves a residue:
    // catan(0) is 1 and catan(1.0) is 0x1FF on the console too (checked against a model of the
    // retail routine written independently from its assembly).
    CHECK(catan(0) == 1 && catan(0x1000) == 0x1FF && catan(-0x1000) == -0x1FF,
          "catan(0) = %d, catan(1.0) = 0x%X, catan(-1.0) = -0x%X", catan(0), catan(0x1000),
          -catan(-0x1000));
}

int main(int argc, char **argv)
{
    const char *exe = argc > 1 ? argv[1] : PORT_DEFAULT_EXE;
    PSX_EXE_INFO info;

    if (psx_mem_init() != 0)
    {
        return 1;
    }
    if (psx_load_exe(exe, &info) != 0 || port_install_stubs() < 0)
    {
        return 1;
    }
    printf("loaded %s: 0x%X bytes at 0x%08X, entry 0x%08X\n", exe, info.t_size, info.t_addr,
           info.pc0);

    test_flags();
    test_retail_data(exe);
    test_literal_alias();
    test_fastmem();
    test_gte();

    test_placement();
    test_emulated();

    printf("harness: %s (%d failure%s)\n", failures ? "FAILED" : "all checks passed", failures,
           failures == 1 ? "" : "s");
    return failures ? 1 : 0;
}
