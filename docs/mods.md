# Mods

The native port has an optional mod system (`port/mods/`). It is compiled into the port only,
never into the matching builds, and it changes no game source: mods hook game functions at their
retail addresses.

## Vanilla or mods

`make play` shows a menu before the Capcom logo:

- **Vanilla**: the original game. No hook is installed and no mod code runs.
- **Mods**: the list of mods to switch on or off, then play.

The menu is skipped when the choice is made elsewhere:

- `make play ARGS="--vanilla"`, or `--mods LIST` (ids separated by commas, `all`, or `none`).
- `[mods] startup = vanilla` or `startup = mods` in `~/.config/megaman-legends/config.ini`
  (`ask` shows the menu). `enabled` lists the mods a modded run switches on.

Headless runs (the smoke and compare tests) are vanilla unless `--mods` is given.

**Saves:** a modded run uses its own memory cards, `card1-mods.mcd` and `card2-mods.mcd`, so
vanilla saves are never written. To bring a vanilla save over, copy `card1.mcd` to
`card1-mods.mcd`.

## The mod panel

In a modded run, open the game's pause menu, then press **M** (keyboard) or **click the right
stick** (gamepad) for the **Mods** panel. Up/Down choose, Left/Right change, Cross opens a mod's
page, Triangle goes back, Start closes. Changes apply at once and are saved to the settings file.

## The mods

| Id | Name | What it does | Settings |
|---|---|---|---|
| `fast_skates` | Faster skates | Faster Jet Skates. Walking, running and enemies are unchanged. | speed: 1.5x, **2x**, 3x |
| `skate_quick_start` | Quick skate start | Holding Circle starts the skates sooner. | start: **Quick** (half the time), Instant |
| `skate_shoot` | Shoot while skating | The buster (and special weapons that can fire on the move) fire on the skates, as in a jump. | |
| `weapon_switch` | Switch special weapon | Equip any special weapon you own from the pause menu. It loads when you unpause. | refill energy: **off**, on |
| `teleport` | Teleport | Go to any room through the game's own door path: choose an area, then a place. | |

Known issue: at high skate speeds Mega Man can clip through doors, because the multiplied step is
applied in one move. Running the move in sub-steps would fix it.

## Writing a mod

1. Add a file in `port/mods/` that defines a `MOD` (see `mods.h`): an id, a name, a sentence for
   its page, its settings as named choices, and `enable(m, on)` to install or remove its hooks.
   Add it to `mods_list.c` and to `MODS_SOURCES` in `port/CMakeLists.txt`. Settings load from
   `[mods] <id>.<key>` and the panel saves them.
2. Hook a function with `orig = mods_hook(RETAIL_ADDR, my_fn)`. `my_fn` has the same signature
   (8- and 16-bit parameters arrive as 32-bit words) and calls `orig` to run the original;
   `mods_unhook` restores it. Every call that reaches the retail address is caught: direct calls,
   calls through the game's routine tables, and calls from interpreted code. Calls the native
   compiler inlined are not, so hook a function that is really called (one in another file, or
   one reached through a table). Check with
   `objdump -d build/port/mml | awk '/<port_native_func_X>:/,/^$/' | grep call`.
   One hook per address: two mods can't hook the same function.
3. Read and write game memory at its PS1 addresses (`MODS_PEEK8`, `MODS_PLAYER_WORK`,
   `MODS_GAME_WORK`), using the game's structures from `include/rock_neo.exe/`.
4. For a page of its own (like Teleport's list), set `page_draw` and `page_input`: the page shows
   the on/off line and, below it, whatever `page_draw` prints with `port_overlay_print`.
   `page_input` gets the newly pressed buttons and returns 1 to hand the cursor back.
5. Test headless with `--mods ID` and the input-script button `mods` (the panel button):
   `press start`, `until 0x800C1B10 == 4 && 0x800C1B11 == 2`, `press mods`, then the panel's
   buttons. The log shows each panel screen.

Stage overlay functions can't be hooked this way yet.
