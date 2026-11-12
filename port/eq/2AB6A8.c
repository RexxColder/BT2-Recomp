#include "common.h"

s32 func_002AB488(s32 arg0);
void func_002A86E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002AB6A8(s32 arg0, s32 arg1) {
    s32 loc[8] = {0}; /* func_002A86E8 copies 0x18+ bytes from this block; the asm leaves loc[4] unwritten */
    s32 count = (arg1 > 0) ? arg1 : -1;

    loc[0] = 0;
    loc[1] = -1;
    loc[2] = -1;
    loc[3] = count;
    loc[5] = arg0;
    func_002A86E8((s32)loc, (s32)func_002AB488, 0, -1);
}
