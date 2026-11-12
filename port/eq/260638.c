#include "common.h"

void StgAabb_SetEmpty(s32 arg0);
s32 func_00269A40(s32 arg0, s32 arg1);
void func_0029DEB8(s32 arg0, s32 arg1, s32 arg2);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
void sceVu0CopyMatrix(s32 arg0, s32 arg1);
void ColBox_AddPoint(s32 arg0, s32 arg1);

void func_00260638(u8 *arg0) {
    u8 sp[0x1F0];
    u8 *s1;
    u8 *s2;
    s32 r;
    f32 x;
    f32 y;
    f32 z;
    f32 nx;
    f32 ny;
    f32 nz;

    s2 = arg0 + 0xF90;
    s1 = (u8 *)*(s32 *)(arg0 + 0x48);
    StgAabb_SetEmpty((s32)(arg0 + 0xF90));
    for (;;) {
        if (*(u16 *)(s1 + 8) != 0) {
            r = func_00269A40((s32)arg0, *(u16 *)(s1 + 0xA));
            func_00312650((s32)sp, (s32)(s1 + 0x40), (s32)(s1 + 0x10));
            func_0029DEB8((s32)(sp + 0x10), r, (s32)sp);
            sceVu0CopyMatrix((s32)(sp + 0x20), r);
            func_003126C8((s32)(sp + 0x50), (s32)(sp + 0x10));

            x = *(f32 *)(s1 + 0x50);
            y = *(f32 *)(s1 + 0x54);
            z = *(f32 *)(s1 + 0x58);
            nx = -x;
            ny = -y;
            nz = -z;

            *(f32 *)(sp + 0x70) = x;
            *(f32 *)(sp + 0x74) = y;
            *(f32 *)(sp + 0x78) = z;
            *(s32 *)(sp + 0x7C) = 0;
            *(f32 *)(sp + 0x144) = y;
            *(f32 *)(sp + 0x150) = x;
            *(f32 *)(sp + 0xF0) = x;
            *(f32 *)(sp + 0xF4) = y;
            *(f32 *)(sp + 0xF8) = z;
            *(f32 *)(sp + 0xFC) = 1.0f;
            *(f32 *)(sp + 0x100) = nx;
            *(f32 *)(sp + 0x104) = y;
            *(f32 *)(sp + 0x108) = z;
            *(f32 *)(sp + 0x10C) = 1.0f;
            *(f32 *)(sp + 0x110) = x;
            *(f32 *)(sp + 0x114) = ny;
            *(f32 *)(sp + 0x118) = z;
            *(f32 *)(sp + 0x11C) = 1.0f;
            *(f32 *)(sp + 0x120) = nx;
            *(f32 *)(sp + 0x124) = ny;
            *(f32 *)(sp + 0x128) = z;
            *(f32 *)(sp + 0x12C) = 1.0f;
            *(f32 *)(sp + 0x130) = x;
            *(f32 *)(sp + 0x134) = y;
            *(f32 *)(sp + 0x138) = nz;
            *(f32 *)(sp + 0x13C) = 1.0f;
            *(f32 *)(sp + 0x140) = nx;
            *(f32 *)(sp + 0x148) = nz;
            *(f32 *)(sp + 0x14C) = 1.0f;
            *(f32 *)(sp + 0x154) = ny;
            *(f32 *)(sp + 0x158) = nz;
            *(f32 *)(sp + 0x15C) = 1.0f;
            *(f32 *)(sp + 0x160) = nx;
            *(f32 *)(sp + 0x164) = ny;
            *(f32 *)(sp + 0x168) = nz;
            *(f32 *)(sp + 0x16C) = 1.0f;

            sceVu0ApplyMatrix((s32)(sp + 0x170), (s32)(sp + 0x20), (s32)(sp + 0xF0));
            sceVu0ApplyMatrix((s32)(sp + 0x180), (s32)(sp + 0x20), (s32)(sp + 0x100));
            sceVu0ApplyMatrix((s32)(sp + 0x190), (s32)(sp + 0x20), (s32)(sp + 0x110));
            sceVu0ApplyMatrix((s32)(sp + 0x1A0), (s32)(sp + 0x20), (s32)(sp + 0x120));
            sceVu0ApplyMatrix((s32)(sp + 0x1B0), (s32)(sp + 0x20), (s32)(sp + 0x130));
            sceVu0ApplyMatrix((s32)(sp + 0x1C0), (s32)(sp + 0x20), (s32)(sp + 0x140));
            sceVu0ApplyMatrix((s32)(sp + 0x1D0), (s32)(sp + 0x20), (s32)(sp + 0x150));
            sceVu0ApplyMatrix((s32)(sp + 0x1E0), (s32)(sp + 0x20), (s32)(sp + 0x160));

            ColBox_AddPoint((s32)s2, (s32)(sp + 0x170));
            ColBox_AddPoint((s32)s2, (s32)(sp + 0x180));
            ColBox_AddPoint((s32)s2, (s32)(sp + 0x190));
            ColBox_AddPoint((s32)s2, (s32)(sp + 0x1A0));
            ColBox_AddPoint((s32)s2, (s32)(sp + 0x1B0));
            ColBox_AddPoint((s32)s2, (s32)(sp + 0x1C0));
            ColBox_AddPoint((s32)s2, (s32)(sp + 0x1D0));
            ColBox_AddPoint((s32)s2, (s32)(sp + 0x1E0));
        }
        if (*(u16 *)(s1 + 6) != 0) {
            return;
        }
        s1 += *(s32 *)s1;
    }
}
