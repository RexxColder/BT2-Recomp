#include "common.h"

s32 func_002E07C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002E0598(s32 arg0, s32 arg1);

extern s32 D_00399DF8 __attribute__((section(".data")));

s32 func_002E0378(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_002E07C0(arg0, arg1, arg2, arg3);
    return func_002E0598(D_00399DF8, 0x1BE0);
}
