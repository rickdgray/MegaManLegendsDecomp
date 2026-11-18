// Shared between mods.c and mods_menu.c; mods use mods.h.
#ifndef PORT_MODS_INTERNAL_H
#define PORT_MODS_INTERNAL_H

#include "mods.h"

enum
{
    MODS_UNSETTLED = -1,
    MODS_VANILLA   = 0,
    MODS_ON        = 1
};

extern int mods_mode;    // MODS_*
extern int mods_started; // mods_start ran (the game program, a modded run)

MOD *mods_find(const char *id);
int mods_count(void);
// The enabled mods' ids, separated by commas (a static buffer).
char *mods_enabled_list(void);
// Switch a mod or change a setting from a menu: applies it, logs it, saves it.
void mods_set_enabled(MOD *m, int on);
void mods_set_value(MOD *m, MOD_SETTING *s, int value);

#endif
