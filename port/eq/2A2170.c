#include "common.h"

extern s32 D_00387EE8;
extern s32 D_00387EF4;

s32 func_002A2170(void) {
    s32 temp_v0;

    temp_v0 = D_00387EF4 * 0x4C;
    D_00387EF4 += 1;
    return D_00387EE8 + temp_v0;
}
