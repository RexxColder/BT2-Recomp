#include "common.h"

void BtlAnim_SetBlend(f32 farg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00217488(s32 arg0);
s32 func_0023C710(s32 arg0);
extern f32 D_003869C0;

s32 func_00235438(s32 arg0) {
    s32 temp_v0;

    if (func_00211310(arg0, 4, 0x02000000) != 0) {
        func_002113C0(arg0, 2, 0x800, 1);
        return 0x97;
    }
    if (func_00211310(arg0, 4, 0x800000) == 0) {
        if (func_00211310(arg0, 2, 1) == 0) {
            return -1;
        }
        BtlAnim_SetBlend(D_003869C0, arg0);
        return func_0023C710(arg0);
    }
    temp_v0 = func_00217488(arg0);
    switch (temp_v0) {
    case 0xBB:
        return 0xC1;
    case 0xBD:
        return 0xC3;
    case 0xBC:
        return 0xC2;
    }
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_003869C0, arg0);
    return func_0023C710(arg0);
}
