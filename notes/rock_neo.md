# ROCK_NEO.EXE (main game)

Not started. Loaded by the shim with `LoadExec("cdrom:\ROCK_NEO.EXE;1", 0x801fff00, 0)`.

## Known so far

- **Confirmed (PCSX-Redux):** after the handoff, ROCK_NEO's code occupies the shim's memory: there
  is ROCK_NEO code at `0x80012094`, and a call to `0x8007a060`. **Suspected:** load address
  `0x80010000` (check the header).
- Expect a linked-in PsyQ library like the shim's, larger (libgte, libgs, libsnd...). The shim's
  object-split method and PsyQ declarations carry over (see [toolchain.md](toolchain.md)).
- **Suspected:** the shim's CD command module (`Cmd_*`, `Cd_*`) is shared, with command types 1–4
  implemented here.

## Prior work: ChrisNonyminus/mml1

A 2023 decompilation attempt on GitHub; no matched C, last commit 2023-07. **No license**, so use
its findings (facts) only; don't copy its files. All of this is **suspected** until verified.

- **`gp` = `0x80097864`**, and the splat config has `.sdata` and `.scommon` sections: ROCK_NEO
  likely uses gp-relative small data, so **`-G8`**, unlike the shim. Run the gp test first.
- **Translation-unit guesses** (file offsets): `main` `0x2490`, `Code800133D8` `0x3BD8`, `game`
  `0x5DA4`, `sound` `0xA0C0`, `cd` `0xBBE4`, `scene` `0xE054`, `player` `0x2C640`, `moji`
  `0x43F88`, `sub_scrn` `0x4F434`, `debug` `0x531E0`, PsyQ `0x587F8`; data `0x70EC4`, sdata
  `0x80064`, scommon `0x88958`, bss `0x8B648`, heap `0xB5E88`; file end `0xC9800`. `rodata`
  starts at `0x800`, as in the shim.
- **Names** (~330), many matched to the TCRF source: all `Sub_screen_*` functions
  (`Sub_screen_cancel_check` `0x80060E64` …), `Map_screen_init` `0x8006259C`, `Map_screen_task`
  `0x800625DC`, `Sound_call` `0x8001A008`, `Cd_read_comb` `0x8001D440`, `Cd_read_sync2`
  `0x8001D838`, `Sce_flag_test` `0x8001DA58`, `Model_Shadow_Trans` `0x8002C794`, `MojiTaskKill`
  `0x80053A30`, `main` `0x80011C90`, init `0x80011F04`, vsync callback `0x800123FC`.
- **Globals:** `Player_work` `0x800B51B0` (`0x5F4` bytes, a second at `0x800B57A4`), `Game_work`
  `0x800C1B10` (`0x210`), `Moji_work` `0x800BB6B8`, `Map_screen_work` `0x800987F0`, `Moji_flag`
  `0x80098A58`, `Sce_flag` `0x800BE378`, `Rock_buster_parts_tbl` `0x8008FE64`.
- **Scratchpad:** `System_timer` `0x1F800002`, `Map_prim_ptr` `0x1F800070`.
- **CD file enum:** `Cd_read_comb(id)` takes a file index; the `CDDATA` files start at index 3
  (`ARM00L_BIN` = 3, ..., alphabetical).
- **Flags guessed (unverified):** gcc 2.7, `-O2 -G8 -funsigned-char -fpeephole -ffunction-cse
  -fpcc-struct-return -fcommon -mgas -msoft-float`. `-funsigned-char` matters wherever plain
  `char` appears.

## To do (recon)

- Header: load address, entry point, sizes.
- `gp` value, then the gp test: are globals reached through `$gp`? Decides `-G0` vs `-G8`.
- The startup code's BSS-clear loop gives the BSS range (the header's fields may be zero, as in
  the shim).
- Code/data/BSS boundaries; compare with the TU guesses above.
- PsyQ library split (Ghidra's `NAME_OBJ_<offset>` labels).
- Compiler probes: does gcc 2.7.2 + ASPSX 2.56 still match? Test `-G8` and `-funsigned-char`.
- Compare the build-timestamp string with the shim's.
- Where the stage overlays are loaded from, and the load addresses in [disc.md](disc.md).
