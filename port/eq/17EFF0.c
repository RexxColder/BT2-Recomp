#include "common.h"

void func_00208DE8(s32 a0, void *a1, s32 a2);
void func_00312638(void *a0, void *a1, void *a2);
void func_00312650(void *a0, void *a1, void *a2);

void func_0017EFF0(void *arg0, s32 arg1) {
    f32 sp[4];
    u8 *s1 = (u8 *)arg0;
    u8 *s0;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    s32 v0;
    s32 v1;
    s32 a1;
    s32 cnt = 0x13;

    do {
        s0 = s1 + 0x5E0;
        if (*(s32 *)(s1 + 0x5B0) & 1) {
            func_00208DE8(arg1, s0, *(s32 *)(s1 + 0x5B4));
            func_00208DE8(arg1, sp, *(s32 *)(s1 + 0x5B8));
            func_00312650(sp, sp, s0);
            f3 = *(f32 *)(s1 + 0x5D4);
            *(f32 *)(s1 + 0x5E0) = *(f32 *)(s1 + 0x5E0) + sp[0] * f3;
            *(f32 *)(s1 + 0x5E4) = *(f32 *)(s1 + 0x5E4) + sp[1] * f3;
            *(f32 *)(s1 + 0x5E8) = *(f32 *)(s1 + 0x5E8) + sp[2] * f3;
            func_00312638(s0, s0, s1 + 0x5F0);
            f2 = *(f32 *)(s1 + 0x60C) + *(f32 *)(s1 + 0x5D0);
            *(f32 *)(s1 + 0x60C) = f2;
            *(f32 *)(s1 + 0x5C8) = *(f32 *)(s1 + 0x5C8) + *(f32 *)(s1 + 0x5CC);
            if (f2 < 0.0f) {
                *(f32 *)(s1 + 0x60C) = 0.0f;
            }
            v1 = *(s32 *)(s1 + 0x5BC);
            a1 = v1 + 1;
            v0 = (v1 + (s32)((u32)v1 >> 31)) >> 1;
            *(s32 *)(s1 + 0x5BC) = a1;
            f1 = (f32)v0 * 0.5f;
            f0 = (f32)(v1 - v0 * 2) * 0.5f;
            *(f32 *)(s1 + 0x614) = f1;
            *(f32 *)(s1 + 0x610) = f0;
            *(f32 *)(s1 + 0x61C) = f1 + 0.5f;
            *(f32 *)(s1 + 0x618) = f0 + 0.5f;
            if (a1 >= 4) {
                *(s32 *)(s1 + 0x5BC) = 0;
            }
            f0 = *(f32 *)(s1 + 0x5C4) - 1.0f;
            *(f32 *)(s1 + 0x5C4) = f0;
            if (f0 < 0.0f) {
                *(s32 *)(s1 + 0x5B0) = 0;
            }
        }
        cnt -= 1;
        s1 += 0x70;
    } while (cnt >= 0);
}
