#include "common.h"

s32 BtlScene_IsEffectStopped(s32 a0, u8 a1);
void BtlTask_SetDead(void *a0);
void func_001EB4E0(void *a0);
void func_001EB5C8(void *a0);

void func_001EB270(void *arg0) {
    u8 *temp_s0;
    u8 *temp_s2;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;
    f32 temp_x;
    s32 temp_t;
    s32 temp_a;
    s32 var_s1;
    s32 var_v1;
    s32 state;

    temp_s0 = *(u8 **)((u8 *)arg0 + 0x38);
    temp_s2 = *(u8 **)(temp_s0 + 0x4);
    if (BtlScene_IsEffectStopped(*(s32 *)(temp_s0 + 0x3C), *(u8 *)(temp_s0 + 0x40)) != 0) {
        return;
    }
    temp_f1 = *(f32 *)(temp_s0 + 0x50);
    if (temp_f1 >= 0.0f) {
        *(f32 *)(temp_s0 + 0x50) = temp_f1 - 1.0f;
        return;
    }

    if (!(*(u16 *)(temp_s0 + 0x60) & 2)) {
        /* cvt.w.s: truncates toward zero */
        temp_f0 = *(f32 *)(temp_s0 + 0x58);
        temp_t = (s32)temp_f0;
        temp_a = temp_t;
        if ((temp_a % *(s32 *)(temp_s2 + 0x120)) == 0) {
            if (*(s32 *)(temp_s2 + 0x124) > 0) {
                var_s1 = 0;
                do {
                    var_s1 += 1;
                    func_001EB4E0(temp_s0);
                } while (var_s1 < *(s32 *)(temp_s2 + 0x124));
            }
        }
    }

    state = *(u8 *)((u8 *)arg0 + 1);
    if (state == 1) {
        var_v1 = *(u16 *)(temp_s0 + 0x60);
        if (var_v1 & 2) {
            *((u8 *)arg0 + 1) = 2;
            var_v1 = *(u16 *)(temp_s0 + 0x60);
        }
    } else if (state < 2) {
        if (state == 0) {
            *((u8 *)arg0 + 1) = 1;
        }
        var_v1 = *(u16 *)(temp_s0 + 0x60);
    } else if (state == 2) {
        if (*(s32 *)(temp_s0 + 0x64) == 0) {
            temp_f1 = *(f32 *)(temp_s0 + 0x54);
            if (!(temp_f1 >= 0.0f)) {
                var_v1 = *(u16 *)(temp_s0 + 0x60) | 4;
                *(u16 *)(temp_s0 + 0x60) = (u16)var_v1;
            } else {
                var_v1 = *(u16 *)(temp_s0 + 0x60);
                *(f32 *)(temp_s0 + 0x54) = temp_f1 - 1.0f;
            }
        } else {
            var_v1 = *(u16 *)(temp_s0 + 0x60);
        }
    } else {
        var_v1 = *(u16 *)(temp_s0 + 0x60);
    }

    if (!(var_v1 & 4)) {
        func_001EB5C8(temp_s0);
        var_v1 = *(u16 *)(temp_s0 + 0x60);
    }
    temp_f3 = *(f32 *)(temp_s0 + 0x5C);
    temp_f2 = *(f32 *)(temp_s0 + 0x58) + 1.0f;
    *(f32 *)(temp_s0 + 0x58) = temp_f2;
    if (temp_f3 > 0.0f) {
        if (temp_f3 <= temp_f2) {
            var_v1 = var_v1 | 2;
            *(u16 *)(temp_s0 + 0x60) = (u16)var_v1;
        }
    }
    if (var_v1 & 4) {
        BtlTask_SetDead(arg0);
    }
}
