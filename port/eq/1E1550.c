#include "common.h"

extern f32 D_00385664;
extern f32 D_00385668;

#define FR_F(off) (*(f32 *)(fr + (off)))
#define FR_W(off) (*(s32 *)(fr + (off)))

void func_001E65C8(f32 *a0, s32 a1, s32 a2, s32 a3);
void func_00312490(f32 *a0, f32 *a1, f32 *a2);
void func_00312638(void *a0, void *a1, void *a2);
void func_00312650(void *a0, void *a1, void *a2);
void func_00312680(f32 f, void *a0, void *a1);
void sceVu0Normalize(void *a0, void *a1);
void func_001E3AC8(f32 f, void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, void *t2,
                   s32 t3, s32 st0);

void func_001E1550(void *arg0, void *arg1, s32 arg2, s32 arg3, f32 farg) {
    u8 fr[0x200];
    u8 *s1 = (u8 *)arg0;
    u8 *s6 = (u8 *)arg1;
    s32 a3m = arg3 & 0xFF;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 vf;
    f32 f0v;
    s32 v;
    s32 k;
    u8 *s3;
    u8 *s0;

    func_001E65C8((f32 *)(fr + 0x10), arg2, s1[0x5C], a3m);
    f22 = 1.0f;
    f21 = f22 / FR_F(0x14);
    f20 = (FR_F(0x10) - f22) / FR_F(0x10);

    FR_F(0x40) = *(f32 *)(s6 + 0);
    FR_F(0x44) = *(f32 *)(s6 + 4);
    FR_F(0x48) = *(f32 *)(s6 + 8);
    FR_F(0x4C) = *(f32 *)(s6 + 0xC);
    FR_F(0x24) = -1.0f;
    FR_W(0x20) = 0;
    FR_W(0x28) = 0;
    FR_F(0x2C) = f22;
    func_00312680(farg, fr + 0x120, s1 + 0x30);

    if (s1[0x16B] != 0) {
        FR_F(0x100) = f20;
        FR_F(0x10C) = f21;
        FR_F(0x90) = f21;
        FR_F(0x94) = f21;
        FR_F(0x98) = f20;
        FR_F(0x9C) = f21;
        FR_F(0xA0) = f21;
        FR_F(0xA4) = f20;
        FR_F(0xA8) = f20;
        FR_F(0xAC) = f20;
        FR_F(0xB0) = f20;
        FR_F(0xB4) = f21;
        FR_F(0xB8) = f21;
        FR_F(0xBC) = f21;
        FR_F(0xC0) = f20;
        FR_F(0xC4) = f20;
        FR_F(0xC8) = f21;
        FR_F(0xCC) = f20;
        FR_F(0xD0) = f21;
        FR_F(0xD4) = f20;
        FR_F(0xD8) = f20;
        FR_F(0xDC) = f20;
        FR_F(0xE0) = f21;
        FR_F(0xE4) = f21;
        FR_F(0xE8) = f20;
        FR_F(0xEC) = f21;
        FR_F(0xF0) = f20;
        FR_F(0xF4) = f20;
        FR_F(0xF8) = f21;
        FR_F(0xFC) = f20;
        FR_F(0x104) = f21;
        FR_F(0x108) = f21;
        func_00312490((f32 *)(fr + 0x30), (f32 *)(fr + 0x40), (f32 *)(fr + 0x20));
        func_00312490((f32 *)(fr + 0x20), (f32 *)(fr + 0x30), (f32 *)(fr + 0x40));
        sceVu0Normalize(fr + 0x30, fr + 0x30);
        sceVu0Normalize(fr + 0x20, fr + 0x20);
        FR_F(0x17C) = f22;
        FR_W(0x170) = 0;
        FR_W(0x174) = 0;
        FR_W(0x178) = 0;
        func_00312680(0.5f, fr + 0x110, fr + 0x120);

        v = *(s32 *)(s1 + 0x50);
        if (v >= 0) {
            vf = (f32)v;
        } else {
            vf = 2.0f * (f32)((v & 1) | ((u32)v >> 1));
        }
        func_00312680(FR_F(0x110) * vf * D_00385664 * 0.5f, fr + 0x130, fr + 0x30);

        v = *(s32 *)(s1 + 0x50);
        if (v >= 0) {
            f0v = (f32)v;
        } else {
            f0v = 2.0f * (f32)((v & 1) | ((u32)v >> 1));
        }
        func_00312680(FR_F(0x114) * f0v * D_00385668 * 0.5f, fr + 0x140, fr + 0x20);

        func_00312638(fr + 0x150, fr + 0x170, fr + 0x130);
        func_00312650(fr + 0x160, fr + 0x170, fr + 0x130);
        func_00312638(fr + 0x50, fr + 0x150, fr + 0x140);
        func_00312638(fr + 0x60, fr + 0x160, fr + 0x140);
        func_00312650(fr + 0x70, fr + 0x150, fr + 0x140);
        func_00312650(fr + 0x80, fr + 0x160, fr + 0x140);

        for (k = 0; k < 4; k++) {
            s3 = fr + 0x50 + k * 0x10;
            s0 = fr + 0x90 + k * 0x20;
            func_001E3AC8(farg, s1 + 0x10, s1 + 0x60, s3, fr + 0x110, s6, s0, s0 + 0x10, a3m, arg2);
        }
    }
}
