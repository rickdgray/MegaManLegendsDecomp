// PsyQ library functions that the matching build still knows by splat names (func_XXXXXXXX).
// The port defines each under its PsyQ
// name and gives it the splat name as an alias, so it links before and after the rename;
// port/tools/gen_link.py accepts several names for one native function at one retail address.
#ifndef PSYQ_ALIAS_H
#define PSYQ_ALIAS_H

#ifdef PORT_SHIM
// The boot shim's build (port/shim.cmake): ROCK_NEO.EXE's splat names mean nothing there, and a
// name like func_8007FF70 would be placed at that address in the shim's memory.
#define PSYQ_SPLAT_ALIAS(splat, name) extern int port_no_alias_##splat
#else
#define PSYQ_SPLAT_ALIAS(splat, name) __typeof__(name) splat __attribute__((alias(#name)))
#endif

#endif
