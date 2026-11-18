// Proves the port's addressing model in a 32-bit process:
//   1. PS1 RAM and scratchpad mapped at their real addresses
//   2. reads and writes through literal PS1 addresses, as the game's macros do
//   3. a pointer stored in a 32-bit struct field, as the game's work areas do
//   4. a call through a retail function address (a jump stub in RAM) reaching native code
//   5. the OT walker's 24-bit tag addresses resolving into the window
#include "psx_mem.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CHECK(cond)                                                                                \
    do                                                                                             \
    {                                                                                              \
        if (!(cond))                                                                               \
        {                                                                                          \
            printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);                                 \
            return 1;                                                                              \
        }                                                                                          \
        printf("ok   %s\n", #cond);                                                                \
    } while (0)

// Shaped like the game's work areas: a pointer kept in a 32-bit field.
typedef struct
{
    uint8_t routine_0, routine_1, routine_2, routine_3;
    uint32_t next; // a pointer in the original
    int16_t x, y;
} TEST_WORK;

static int native_add(int a, int b)
{
    return a * 100 + b;
}

typedef int (*ADD_FUNC)(int, int);

int main(void)
{
    TEST_WORK *wp;
    ADD_FUNC f;

    printf("sizeof(void *) = %u, sizeof(long) = %u\n", (unsigned)sizeof(void *),
           (unsigned)sizeof(long));
    CHECK(sizeof(void *) == 4);
    CHECK(psx_mem_init() == 0);

    // 2. Literal addresses, the way include/rock_neo.exe headers write them.
    *(uint32_t *)0x801F8100 = 0xCAFEF00D; // the thread table
    *(uint8_t *)0x1F800074  = 0x5A;       // a scratchpad byte (C8002D9A0_SHIFT)
    *(uint32_t *)0x1F8003FC = 0x12345678; // last scratchpad word
    CHECK(*(volatile uint32_t *)psx_ptr(0x801F8100) == 0xCAFEF00D);
    CHECK(*(volatile uint32_t *)psx_ptr(0x001F8100) == 0xCAFEF00D); // KUSEG mirror
    CHECK(*(volatile uint32_t *)psx_ptr(0xA01F8100) == 0xCAFEF00D); // KSEG1 mirror
    CHECK(*(volatile uint8_t *)0x1F800074 == 0x5A);
    CHECK(*(volatile uint32_t *)0x1F8003FC == 0x12345678);
    CHECK(*(volatile uint32_t *)(0x80000000 + 0x1FFFFC) == 0); // top of the 2 MB, untouched

    // 3. Pointers in 32-bit fields.
    wp                                    = (TEST_WORK *)0x800C1B10;
    wp->next                              = (uint32_t)(uintptr_t)(TEST_WORK *)0x800C1B20;
    ((TEST_WORK *)(uintptr_t)wp->next)->x = -7;
    CHECK(((TEST_WORK *)0x800C1B20)->x == -7);
    CHECK(sizeof(TEST_WORK) == 12);

    // 4. A retail function address that calls native code.
    CHECK(psx_install_stub(0x80012A5C, (void (*)(void))native_add) == 0);
    *(uint32_t *)0x80098000 = 0x80012A5C; // a dispatch-table slot holding the retail address
    f                       = (ADD_FUNC)(uintptr_t)*(uint32_t *)0x80098000;
    CHECK(f(4, 2) == 402);

    // 5. 24-bit ordering-table addresses.
    CHECK(psx_ptr(0x00100000) == (void *)0x80100000);
    CHECK(psx_ptr(0x00FFFFF0) == (void *)0x80FFFFF0);
    CHECK(psx_ptr(0x12345678) == NULL);

    printf("memtest: all checks passed\n");
    return 0;
}
