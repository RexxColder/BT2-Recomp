#include "common.h"

extern u8 *D_003876A0;
extern f32 D_00386EE0;
extern f32 D_00386EE4;
extern f32 D_00386EE8;

void *memcpy(void *arg0, void *arg1, u32 arg2);
s32 BtlStage_IsReady(void);
s32 func_00276D80(void);
void ColBox_GetCenter(u8 *a0, f32 *a1);
void ColBox_GetHalf(u8 *a0, f32 *a1);
void ColBox_SetCenterHalf(u8 *a0, f32 *a1, f32 *a2);
void func_0011E5B0(u8 *a0, u8 *a1);

/* 0x00269400: refreshes the collision box at arg0+0xEAC: copies the 24-byte box at +0xF90 into
 * +0xE94 and +0xEAC, then re-centres it with the half-size scaled by a stage flag. */
void func_00269400(u8 *arg0) {
    u8 *s1;
    u8 *s4;
    u8 *s2;
    u8 *s0;
    f32 center[4];
    f32 half[4];
    f32 k;

    s1 = arg0;
    s4 = s1 + 0xE90;
    s2 = *(u8 **)s4;
    if (s2 == NULL) {
        return;
    }
    if (BtlStage_IsReady() == 0) {
        return;
    }
    if (func_00276D80() == 1) {
        return;
    }
    *(s32 *)(s2 + 0x10) = 0;
    *(s32 *)(s2 + 0x18) = 0;
    s0 = s1 + 0xEAC;
    memcpy(s1 + 0xE94, s1 + 0xF90, 0x18);
    memcpy(s0, s1 + 0xF90, 0x18);

    ColBox_GetCenter(s0, center);
    ColBox_GetHalf(s0, half);
    if ((*(u64 *)(D_003876A0 + 0x4D8) & 2) != 0) {
        *(u8 *)(s2 + 0xD) = 1;
        half[0] = half[0] * D_00386EE0;
        half[2] = half[2] * D_00386EE0;
    } else {
        if (50.0f < *(f32 *)(s1 + 0xFAC)) {
            *(u8 *)(s2 + 0xD) = 1;
            k = D_00386EE4;
        } else {
            *(u8 *)(s2 + 0xD) = 0;
            k = D_00386EE8;
        }
        half[0] = half[0] * k;
        half[2] = half[2] * k;
    }
    ColBox_SetCenterHalf(s0, center, half);

    half[1] = (half[1] + half[1] + 50.0f) * 0.5f;
    center[1] = *(f32 *)(s1 + 0xEB0) + half[1];
    ColBox_SetCenterHalf(s0, center, half);
    func_0011E5B0(*(u8 **)(s1 + 0x9F0), s4);
}
