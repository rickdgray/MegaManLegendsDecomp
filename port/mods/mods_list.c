// The mods the port has, in the menus' order. A new mod: a file in port/mods/ defining a MOD
// (mods.h; mod_fast_skates.c is the example), its extern line here and an entry in the list,
// and its source in MODS_SOURCES (port/CMakeLists.txt).
#include "mods.h"

#include <stddef.h>

extern MOD mod_fast_skates;
extern MOD mod_skate_shoot;
extern MOD mod_skate_quick_start;
extern MOD mod_teleport;
extern MOD mod_weapon_switch;

MOD *const mods_list[] = {
    &mod_fast_skates,
    &mod_skate_shoot,
    &mod_skate_quick_start,
    &mod_teleport,
    &mod_weapon_switch,
    NULL,
};
