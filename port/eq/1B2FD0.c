#include "common.h"

s32 BtlScene_IsEffectStopped(s32 arg0, s32 arg1);
void BtlTask_SetDead(u8 *arg0, s32 arg1);
s32 func_001B26B8(u8 *arg0);
void func_001B2990(u8 *arg0, s32 arg1);
void func_001B2CD0(u8 *arg0, u8 *arg1);

void EftChain2_Update(u8 *arg0) {
    u8 *s0;
    s32 s2;
    s32 a0;
    s32 a1;
    s32 v0;
    s32 flag4;

    s2 = 0;
    s0 = *(u8 **)(arg0 + 0x38);
    if (BtlScene_IsEffectStopped(*(s32 *)s0, *(u8 *)(s0 + 0xA44)) == 0) {
        a1 = *(s32 *)(s0 + 0xA40);
        v0 = a1 & 2;
        if (v0 == 0 || *(f32 *)(s0 + 0xA64) > 0.0f) {
            if (*(f32 *)(s0 + 0xA60) <= 0.0f) {
                if (*(f32 *)(s0 + 0xA5C) <= 0.0f) {
                    func_001B2990(arg0, a1);
                    a1 = *(s32 *)(s0 + 0xA40);
                } else {
                    *(f32 *)(s0 + 0xA5C) = *(f32 *)(s0 + 0xA5C) - 1.0f;
                }
            } else {
                *(f32 *)(s0 + 0xA60) = *(f32 *)(s0 + 0xA60) - 1.0f;
            }
            v0 = a1 & 2;
        }
        if (v0 != 0) {
            if (0.0f < *(f32 *)(s0 + 0xA64)) {
                *(f32 *)(s0 + 0xA64) = *(f32 *)(s0 + 0xA64) - 1.0f;
            }
        }
        func_001B26B8(arg0);
        a1 = *(s32 *)(s0 + 0xA40);
        v0 = a1 & 2;
        if ((a1 & 8) == 0 && *(f32 *)(s0 + 0xA60) <= 0.0f) {
            *(f32 *)(s0 + 0xA54) = *(f32 *)(s0 + 0xA54) + 1.0f;
            if (*(f32 *)(s0 + 0xA58) <= *(f32 *)(s0 + 0xA54)) {
                a1 = a1 | 2;
                *(s32 *)(s0 + 0xA40) = a1;
                v0 = a1 & 2;
            }
        }
        flag4 = a1 & 4;
        if (v0 != 0 && *(f32 *)(s0 + 0xA64) <= 0.0f) {
            a0 = 0;
            if (*(s32 *)(s0 + 0x48) != 0) {
                s2 = 1;
            } else {
                a0 = 1;
                while (a0 < 16) {
                    if (*(s32 *)(s0 + a0 * 0xA0 + 0x48) != 0) {
                        s2 = 1;
                        break;
                    }
                    a0 += 1;
                }
            }
            flag4 = a1 & 4;
            if (s2 == 0) {
                a1 = a1 | 4;
                *(s32 *)(s0 + 0xA40) = a1;
                flag4 = a1 & 4;
            }
        }
    } else {
        flag4 = *(s32 *)(s0 + 0xA40) & 4;
        a1 = *(s32 *)(s0 + 0xA40);
    }
    if (flag4 != 0) {
        BtlTask_SetDead(arg0, a1);
        return;
    }
    func_001B2CD0(s0, s0);
}
