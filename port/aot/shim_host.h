#ifndef PORT_AOT_SHIM_HOST_H
#define PORT_AOT_SHIM_HOST_H

#include "shim.h"

void port_aot_shim_start(w2c_shim *shim);
void port_aot_shim_finish(w2c_shim *shim);
// Run an initialized shim until it requests ROCK_NEO.EXE via LoadExec.
int port_aot_shim_wait_for_loadexec(w2c_shim *shim);

#endif
