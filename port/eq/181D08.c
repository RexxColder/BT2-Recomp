#include "common.h"

s32 BtlScene_IsTimeStopped(s32 arg0);
void BtlTask_SetDead(u8 *arg0);
void func_00181B10(u8 *arg0);

void func_00181D08(u8 *arg0) {
    u8 *s0;
    s32 v;
    f32 f;

    s0 = *(u8 **)(arg0 + 0x38);
    if (BtlScene_IsTimeStopped((s32)arg0) == 0) {
        v = *(s32 *)(s0 + 0x98);
        if (v & 1) {
            func_00181B10(arg0);
            v = *(s32 *)(s0 + 0x98);
        }
        f = *(f32 *)(s0 + 0x90) - 1.0f;
        *(f32 *)(s0 + 0x90) = f;
        if (f <= 0.0f) {
            v = v | 2;
            *(s32 *)(s0 + 0x98) = v;
        }
        if (v & 2) {
            BtlTask_SetDead(arg0);
        }
    }
}
