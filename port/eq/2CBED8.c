#include "common.h"

s32 func_002CE750(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 sceMpegCreate(s32 arg0, s32 arg1, s32 arg2);
s32 sceMpegAddCallback(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002CC3B0(s32 arg0, s32 arg1);
void func_002CB3D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_002CB748(s32 arg0);
void func_002CB948(s32 arg0);
void func_002CC100(void);
void func_002CC208(void);
void func_002CC2B0(void);
void func_002CC2D8(void);
extern s32 D_00346E5C __attribute__((section(".data")));

void func_002CBED8(u8 *arg0) {
    u8 *m;
    u8 *a2;
    u8 *s1;
    u8 *s3;
    u8 *fp;
    s32 s0;
    s32 s4;
    s32 s5;
    s32 s6;
    s32 s7;
    s32 a3;
    s32 v0;
    s32 prod;
    s32 nine;

    m = *(u8 **)(arg0 + 0x1FC0);
    a2 = m + 4;
    s1 = m + 0x1128;
    s3 = m + 0x1150;
    fp = m + 0x11F8;
    if (D_00346E5C == 0) {
        *(s32 *)s1 = 0;
        return;
    }
    a3 = *(s32 *)(m + 0x28);
    prod = (s32)((u32)*(s32 *)(a2 + 0x8) * (u32)*(s32 *)(a2 + 0xC));
    nine = (s32)((u32)prod * 9u);
    s4 = nine / 2 + 0x2800;
    if (a3 == 0) {
        v0 = (*(s32 *)(a2 + 0x10) + 0x3F) & ~0x3F;
        *(s32 *)(m + 0x28) = v0;
        v0 = (v0 + s4 + 0x3F) & ~0x3F;
    } else {
        v0 = (*(s32 *)(m + 0x2C) + 0x3F) & ~0x3F;
        *(s32 *)(m + 0x28) = (a3 + 0x3F) & ~0x3F;
    }
    *(s32 *)(m + 0x2C) = v0;
    s6 = *(s32 *)(m + 0x2C);
    s0 = *(s32 *)(m + 0x28);
    s5 = (s6 + 0x8003F) & ~0x3F;
    s7 = (s5 + 0x104F) & ~0x3F;
    if (func_002CE750(-0x40, (s32)m, (s32)a2, a3) != 1) {
        sceMpegCreate((s32)s3, s0, s4);
        sceMpegAddCallback((s32)s3, 0, (s32)func_002CC100, (s32)arg0);
        sceMpegAddCallback((s32)s3, 1, (s32)func_002CC208, (s32)arg0);
        sceMpegAddCallback((s32)s3, 2, (s32)func_002CC2B0, (s32)arg0);
        sceMpegAddCallback((s32)s3, 3, (s32)func_002CC2D8, (s32)arg0);
    } else {
        func_002CC3B0((s32)arg0, s0);
    }
    s0 = (s32)(s1 + 0x70);
    func_002CB3D0(s0, s6, s5, 0x100, s7, 0x200);
    func_002CB748(s0);
    func_002CB948(s0);
    s1[0x10] = 0;
    s1[0x11] = 0;
    s1[0x12] = 0;
    *(s32 *)s1 = 1;
    *(s32 *)(s1 + 0x20) = 0;
    *(s32 *)fp = -1;
    *(s32 *)(fp + 4) = 0;
    *(s32 *)(s1 + 0x4) = 0;
    *(s32 *)(s1 + 0x8) = 0;
    *(s32 *)(s1 + 0xC) = 0;
    *(s32 *)(s1 + 0x14) = 0;
    *(s32 *)(s1 + 0x18) = 0;
    *(s32 *)(s1 + 0x1C) = 0;
}
