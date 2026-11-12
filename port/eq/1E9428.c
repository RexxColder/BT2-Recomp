#include "common.h"

s32 BtlScene_IsEffectStopped(s32 arg0, s32 arg1);
void BtlTask_SetDead(s32 arg0);
s32 func_001E9610(s32 arg0);
void func_001E96B8(s32 arg0);
void func_001EA518(s32 arg0);

void func_001E9428(u8 *arg0) {
    u8 *s0;
    f32 f1;

    s0 = *(u8 **)(arg0 + 0x38);
    if (BtlScene_IsEffectStopped(*(s32 *)(s0 + 0x120), *(u8 *)(s0 + 0x126)) == 0) {
        switch (arg0[1]) {
        case 0:
            f1 = *(f32 *)(s0 + 0xC0);
            if (f1 >= 0.0f) {
                *(f32 *)(s0 + 0xC0) = f1 - 1.0f;
            } else if (func_001E9610((s32)s0) == 0) {
                *(u16 *)(s0 + 0x124) = (u16)(*(u16 *)(s0 + 0x124) | 0x10);
            } else {
                arg0[1] = (u8)(arg0[1] + 1);
            }
            break;
        case 2:
            *(u16 *)(s0 + 0x124) = (u16)(*(u16 *)(s0 + 0x124) | 0x10);
            break;
        case 1:
            if (*(u16 *)(s0 + 0x124) & 4) {
                arg0[1] = 2;
            }
            break;
        default:
            break;
        }
        if (arg0[1] != 0 && !(*(u16 *)(s0 + 0x124) & 0x10)) {
            func_001E96B8((s32)s0);
        }
    }
    func_001EA518((s32)s0);
    if (*(u16 *)(s0 + 0x124) & 0x10) {
        BtlTask_SetDead((s32)arg0);
    }
}
