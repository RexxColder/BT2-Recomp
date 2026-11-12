#include "common.h"

void BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00212DD8(s32 arg0, s32 arg1);
s32 func_0023CDF8(s32 arg0, s32 arg1);
extern f32 D_00386A80;

s32 func_00237D40(u8 *arg0) {
    if (func_00211310((s32)arg0, 2, 1) != 0) {
        BtlAnim_SetBlend((s32)arg0, D_00386A80);
        func_00212DD8((s32)arg0, 2);
        if (arg0[0xB54] != 0) {
            func_002113C0((s32)arg0, 2, 0x1000, 1);
        }
        return func_0023CDF8((s32)arg0, *(s32 *)(arg0 + 0xB4C));
    }
    return -1;
}
