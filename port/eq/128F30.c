#include "common.h"
#include "vu0_state.h"

/* 0x00128F30 Vu0Cur_GetStackDepth: (s16)vi15 / 4 (rounded toward zero). vi15 is the VU0 stack pointer the C code
   keeps in gVu0 (vsqi / vlqd); on the fallback it read the recompiler's own vi15. */
s32 Vu0Cur_GetStackDepth(void) {
    s32 v = (s16)gVu0.vi[15];

    return (v < 0 ? v + 3 : v) >> 2;
}

/* 0x00128F58 Vu0Cur_IsStackUsed: 1 when the VU0 stack is not empty. */
s32 Vu0Cur_IsStackUsed(void) {
    return Vu0Cur_GetStackDepth() != 0;
}
