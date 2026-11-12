#include "common.h"

void StgAabb_SetEmpty(s32 arg0);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_0029DEB8(s32 arg0, s32 arg1, s32 arg2);
void sceVu0CopyMatrix(s32 arg0, s32 arg1);
void func_003126C8(s32 arg0, s32 arg1);
void ColObb_Update(s32 arg0, s32 arg1);
void func_00260248(s32 arg0, s32 arg1);
void ColBox_AddPoint(s32 arg0, s32 arg1);
void ColBounds_AddSphere(s32 arg0, s32 arg1);

void func_00260340(u8 *arg0) {
    u8 buf[0x80] __attribute__((aligned(16)));
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    s32 flag;

    s2 = arg0 + 0x70;
    s3 = arg0 + 0x88;
    s1 = *(u8 **)arg0;
    StgAabb_SetEmpty((s32)s2);
    StgAabb_SetEmpty((s32)s3);
    do {
        s0 = s1 + 0x20;
        func_00312650((s32)buf, (s32)(s1 + 0x10), *(s32 *)(s1 + 8) + 0x10);
        func_0029DEB8((s32)(buf + 0x10), *(s32 *)(s1 + 0xC), (s32)buf);
        sceVu0CopyMatrix((s32)(buf + 0x20), *(s32 *)(s1 + 0xC));
        func_003126C8((s32)(buf + 0x50), (s32)(buf + 0x10));
        ColObb_Update((s32)(s1 + 0x40), (s32)(buf + 0x20));
        func_00260248((s32)s0, (s32)(buf + 0x50));
        ColBox_AddPoint((s32)s2, (s32)(s1 + 0x150));
        ColBox_AddPoint((s32)s2, (s32)(s1 + 0x160));
        ColBox_AddPoint((s32)s2, (s32)(s1 + 0x170));
        ColBox_AddPoint((s32)s2, (s32)(s1 + 0x180));
        ColBox_AddPoint((s32)s2, (s32)(s1 + 0x190));
        ColBox_AddPoint((s32)s2, (s32)(s1 + 0x1A0));
        ColBox_AddPoint((s32)s2, (s32)(s1 + 0x1B0));
        ColBox_AddPoint((s32)s2, (s32)(s1 + 0x1C0));
        ColBounds_AddSphere((s32)s3, (s32)s0);
        flag = *(s32 *)s1 & 1;
        s1 += 0x1D0;
    } while (flag == 0);
}
