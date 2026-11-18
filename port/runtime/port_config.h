// The player's settings: an INI file, `$XDG_CONFIG_HOME/megaman-legends/config.ini` (default
// `~/.config/megaman-legends/config.ini`; `--config FILE` picks another). Saves live in
// `$XDG_DATA_HOME/megaman-legends/` (default `~/.local/share/megaman-legends/`).
//
// The defaults are the commented file below (port_config_default_text); it is written out on the
// first start of a windowed game when no config file exists, so there is something to edit.
// Keys missing from the user's file keep their defaults. Format: `[section]`, `key = value`,
// `#` or `;` comments.
#ifndef PORT_CONFIG_H
#define PORT_CONFIG_H

// Loads the defaults, then `path` (NULL: the XDG location). Returns 0, or -1 if the file exists
// but cannot be read. `write_default`: create the file with the defaults when it is missing.
int port_config_load(const char *path, int write_default);
const char *port_config_file(void);

// The value of section.key (strings as written, trimmed), or NULL.
const char *port_config_get(const char *section, const char *key);
int port_config_int(const char *section, const char *key, int fallback);
// 1 for 1/yes/true/on, 0 for 0/no/false/off, else `fallback`.
int port_config_bool(const char *section, const char *key, int fallback);
// Overrides one value (command-line options).
void port_config_set(const char *section, const char *key, const char *value);
// Sets one value and writes it into the settings file (the mod menus): the key's line is
// replaced, or added at the end of its section, or the section is added; the rest of the file
// stays as it was. A missing file is written with the defaults first. Returns 0 or -1.
int port_config_save(const char *section, const char *key, const char *value);

// Calls fn for every key of a section, in file order (defaults first, then the user's).
void port_config_each(const char *section, void (*fn)(const char *key, const char *value, void *),
                      void *ctx);

// `$XDG_DATA_HOME/megaman-legends/<name>`; an absolute `name` is returned as is. The string is
// allocated.
char *port_data_path(const char *name);

// Points the memory-card slots at the configured images ([cards] slot1/slot2).
void port_config_apply_cards(void);

extern const char port_config_default_text[];

#endif
