#include "common.h"

extern u8 D_0036E1F0[] __attribute__((section(".data")));

s32 func_00158060(s32 a0);
s32 func_0020B3D0(s32 a0);
void func_00129C28(void *a0, void *a1);
void func_00208DE8(s32 a0, void *a1, s32 a2);
void Vec3_Add(void *a0, void *a1, void *a2);
void func_0019F8D0(void *a0, s64 a1, s64 a2);
void func_001DBF28(void *a0, s64 a1, s64 a2, s64 a3, s64 t0);

void func_00158108(void *arg0) {
    s64 fr[0x20];
    u8 *F;
    u8 *temp_s2;
    s32 *temp_s3;
    u8 *temp_s0;
    s32 temp_s1;
    s32 temp_s6;

    F = (u8 *)fr;
    temp_s2 = *(u8 **)((u8 *)arg0 + 0x38);
    temp_s3 = *(s32 **)(temp_s2 + 0xA0);
    temp_s0 = temp_s2 + 0x70;
    temp_s1 = func_00158060(func_0020B3D0(*temp_s3));
    temp_s6 = func_00158060(*temp_s3);
    if (*(s32 *)(temp_s2 + 0x10) == 0) {
        func_00208DE8(*temp_s3, F, *(s32 *)(temp_s2 + 8));
        func_00129C28(temp_s2 + 0x40, F);
        func_00129C28(temp_s2 + 0x80, temp_s0);
        Vec3_Add(temp_s0, temp_s0, temp_s2 + 0x90);
        if (temp_s1 & 0x40) {
            *(s64 *)(F + 0x10) = *(s64 *)(D_0036E1F0 + 0x0);
            *(s64 *)(F + 0x18) = *(s64 *)(D_0036E1F0 + 0x8);
            *(s64 *)(F + 0x20) = *(s64 *)(D_0036E1F0 + 0x10);
            *(s64 *)(F + 0x28) = *(s64 *)(D_0036E1F0 + 0x18);
            func_0019F8D0(F + 0x10, *(s64 *)(D_0036E1F0 + 0x10), *(s64 *)(D_0036E1F0 + 0x18));
            *(f32 *)(F + 0x60) = *(f32 *)(temp_s2 + 0x40);
            *(f32 *)(F + 0x64) = *(f32 *)(temp_s2 + 0x44);
            *(f32 *)(F + 0x68) = *(f32 *)(temp_s2 + 0x48);
            *(f32 *)(F + 0x6C) = 1.0f;
            *(s32 *)(F + 0x74) = 0x47;
            *(s32 *)(F + 0x70) = *temp_s3;
            *(s32 *)(F + 0x78) = 1;
            *(s32 *)(F + 0x7C) = 1;
            *(s32 *)(F + 0x80) = 0;
            /* struct at sp+0x30: copies of the 8-byte words above (raw bits) */
            *(s64 *)(F + 0x30) = *(s64 *)(F + 0x60);
            *(s64 *)(F + 0x38) = *(s64 *)(F + 0x68);
            *(s64 *)(F + 0x40) = *(s64 *)(F + 0x70);
            *(s64 *)(F + 0x48) = *(s64 *)(F + 0x78);
            *(s64 *)(F + 0x50) = *(s64 *)(F + 0x80);
            *(s64 *)(F + 0x58) = *(s64 *)(F + 0x88);
            func_001DBF28(F + 0x30, *(s64 *)(F + 0x70), *(s64 *)(F + 0x78), *(s64 *)(F + 0x60), *(s64 *)(F + 0x88));
            *(s32 *)(F + 0x50) = 4;
            func_001DBF28(F + 0x30, *(s64 *)(F + 0x70), *(s64 *)(F + 0x78), *(s64 *)(F + 0x60), *(s64 *)(F + 0x88));
            *(s32 *)(F + 0x50) = 0xA;
            func_001DBF28(F + 0x30, *(s64 *)(F + 0x70), *(s64 *)(F + 0x78), *(s64 *)(F + 0x60), *(s64 *)(F + 0x88));
            *(s32 *)(F + 0x50) = 0xE;
            func_001DBF28(F + 0x30, *(s64 *)(F + 0x70), *(s64 *)(F + 0x78), *(s64 *)(F + 0x60), *(s64 *)(F + 0x88));
            *(s32 *)(F + 0x50) = 0x15;
            func_001DBF28(F + 0x30, *(s64 *)(F + 0x70), *(s64 *)(F + 0x78), *(s64 *)(F + 0x60), *(s64 *)(F + 0x88));
            *(s32 *)(temp_s2 + 0x10) = 1;
        }
    }
    if (temp_s6 & 8) {
        *(s32 *)temp_s2 = *(s32 *)temp_s2 | 1;
        *((u8 *)arg0 + 1) = 5;
    }
}
