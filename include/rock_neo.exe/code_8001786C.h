#ifndef CODE_8001786C_H
#define CODE_8001786C_H

#include "common.h"
#include "psyq/libgpu.h"

// Pool variables (lui-based here, so defined in another file; owners unknown).
// Two full-screen semi-transparent TILEs and their DR_MODEs (tpage from GetTPage), one per
// buffer; set up by func_8001326C (main) and func_80017C30, used by func_80017B24.
extern TILE D_80098A28[2];
extern DR_MODE D_80098A10[2];
extern uint8 D_80098A6A;  // stepped by func_800180D4/func_800181D4 when their sub-step ends
extern sint8 D_80098A6B;  // sub-step of func_800180D4/func_800181D4
extern sint32 D_80098810; // set to 1 by func_800180D4
extern sint32 D_80098824; // set to 1 by func_800180D4
extern sint32 D_80098864; // set to 1 by func_800180D4; main picks D_800806EC's row by it

void func_800178FC(void); // called once per frame by main
void func_80017B24(void); // called once per frame by main
void func_80017C30(sint32 arg0);

#endif
