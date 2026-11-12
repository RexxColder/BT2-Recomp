#include "common.h"

#define SPH(o) (*(u16 *)&sp[o])
#define SPW(o) (*(s32 *)&sp[o])
#define SPF(o) (*(f32 *)&sp[o])

extern u8 *D_0038781C;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

void func_001A3928(u8 *a0, u8 *a1, u8 *a2, s32 a3);
void func_00129C50(u8 *a0, u8 *a1, u8 *a2);
void func_00129440(u8 *a0, u8 *a1, s32 a2);
void func_00129BD0(f32 f12, u8 *a0, s32 a1, s32 *a2);
void func_00129D40(u8 *a0, u8 *a1, s64 a2, s64 a3);

void func_001A3A38(u8 **arg0, s32 arg1) {
    u8 sp[0x150];
    u8 **spE0;
    s32 spE4;
    u8 *s5;
    u8 *s0;
    u8 *s3;
    u8 *v1;
    s32 *a2p;
    s32 s2;
    s32 s4;
    s32 s6;
    s32 t;
    s32 a2u;
    s64 fp;
    s64 c2;
    s64 c3;
    f32 f0;
    f32 f12;

    spE0 = arg0;
    s5 = *arg0;
    if (s5 == NULL) {
        return;
    }
    spE4 = arg1 + 0x10;
    fp = ((s64)0xFF000000 << 32) | 0xFFFFFFFF;

loop_2:
    func_001A3928(sp, s5 + 0x60, s5 + 0x70, spE4);
    s6 = 0;
    s4 = 0;
    s3 = s5 + 0xA0;
    while (s4 < 4) {
        s2 = s4 << 4;
        func_00129C50(sp + 0x40, sp, s3);
        s3 += 0x10;
        s0 = sp + 0x90 + s2;
        func_00129440(s0, sp + 0x40, 1);
        s4 += 1;
        a2p = (s32 *)(sp + 0x9C + s2);
        if (0xFFF0U < *(u32 *)s0) {
            s6 = 1;
            goto after_loop;
        }
        if (0xFFF0U < *(u32 *)(s0 + 4)) {
            s6 = 1;
            goto after_loop;
        }
        if (*(s32 *)(s0 + 8) < 0) {
            s6 = 1;
            goto after_loop;
        }
        f0 = (f32)*a2p;
        f12 = 1.0f / f0;
        if (*(s32 *)s5 & 0x20) {
            func_00129BD0(f12, sp + 0x50 + s2, *(s32 *)(D_0038781C + 8) + s2 + 0xC0, a2p);
        } else {
            func_00129BD0(f12, sp + 0x50 + s2, *(s32 *)(D_0038781C + 8) + s2 + 0x80, a2p);
        }
    }

after_loop:
    if (s6 == 0) {
        s0 = D_00387AD8;
        D_00387AD8 = s0 + 0x90;
        if (s0 == NULL) {
            return;
        }
        c2 = ((s64)0xE4000000 << 32) | 0x8001;
        c3 = (((((s64)0x421421 << 16) | 0x4214) << 16) | 0x2160);
        *(s64 *)(s0 + 0x20) = 0x5C;
        *(s64 *)(s0 + 0x00) = (s64)0xA0000008;
        *(s64 *)(s0 + 0x10) = c2;
        *(s64 *)(s0 + 0x18) = c3;
        func_00129D40(sp + 0xD0, s5 + 0x80, c2, c3);
        s0[0x30] = sp[0xD0];
        s0[0x31] = sp[0xD4];
        s0[0x32] = sp[0xD8];
        s0[0x33] = sp[0xDC];
        *(f32 *)(s0 + 0x34) = SPF(0x58);
        s0[0x48] = sp[0xD0];
        s0[0x49] = sp[0xD4];
        s0[0x4A] = sp[0xD8];
        s0[0x4B] = sp[0xDC];
        *(f32 *)(s0 + 0x4C) = SPF(0x68);
        s0[0x60] = sp[0xD0];
        s0[0x61] = sp[0xD4];
        s0[0x62] = sp[0xD8];
        s0[0x63] = sp[0xDC];
        *(f32 *)(s0 + 0x64) = SPF(0x78);
        s0[0x78] = sp[0xD0];
        s0[0x79] = sp[0xD4];
        s0[0x7A] = sp[0xD8];
        s0[0x7B] = sp[0xDC];
        *(f32 *)(s0 + 0x7C) = SPF(0x88);
        *(f32 *)(s0 + 0x38) = SPF(0x50);
        *(f32 *)(s0 + 0x3C) = SPF(0x54);
        *(f32 *)(s0 + 0x50) = SPF(0x60);
        *(f32 *)(s0 + 0x54) = SPF(0x64);
        *(f32 *)(s0 + 0x68) = SPF(0x70);
        *(f32 *)(s0 + 0x6C) = SPF(0x74);
        *(f32 *)(s0 + 0x80) = SPF(0x80);
        *(f32 *)(s0 + 0x84) = SPF(0x84);
        *(u16 *)(s0 + 0x40) = SPH(0x90);
        *(u16 *)(s0 + 0x42) = SPH(0x94);
        *(s64 *)(s0 + 0x40) = (*(s64 *)(s0 + 0x40) & fp) | ((s64)(SPW(0x98) & 0xFFFFFF) << 32);
        s0[0x47] = 0xFF;
        *(u16 *)(s0 + 0x58) = SPH(0xA0);
        *(u16 *)(s0 + 0x5A) = SPH(0xA4);
        *(s64 *)(s0 + 0x58) = (*(s64 *)(s0 + 0x58) & fp) | ((s64)(SPW(0xA8) & 0xFFFFFF) << 32);
        s0[0x5F] = 0xFF;
        *(u16 *)(s0 + 0x70) = SPH(0xB0);
        *(u16 *)(s0 + 0x72) = SPH(0xB4);
        *(s64 *)(s0 + 0x70) = (*(s64 *)(s0 + 0x70) & fp) | ((s64)(SPW(0xB8) & 0xFFFFFF) << 32);
        s0[0x77] = 0xFF;
        *(u16 *)(s0 + 0x88) = SPH(0xC0);
        *(u16 *)(s0 + 0x8A) = SPH(0xC4);
        *(s64 *)(s0 + 0x88) = (*(s64 *)(s0 + 0x88) & fp) | ((s64)(SPW(0xC8) & 0xFFFFFF) << 32);
        s0[0x8F] = 0xFF;
        *(s64 *)(s0 + 0x28) = *(s64 *)((u8 *)spE0 + s5[5] * 8 + 0x148);
        t = (SPW(0x98) + SPW(0xC8) + (SPW(0xB8) + SPW(0xA8))) >> 10;
        a2u = s5[6];
        if (t < 0) {
            v1 = D_00387AE0 + a2u * 8;
        } else if (t < 0x1000) {
            v1 = D_00387AE0 + (t * 2 + a2u) * 8;
        } else {
            v1 = D_00387AE0 + a2u * 8 + 0xFFF0;
        }
        *(u8 **)(*(u8 **)(v1 + 4) + 4) = s0;
        *(u8 **)(v1 + 4) = s0;
    }

    s5 = *(u8 **)(s5 + 0x120);
    if (s5 != NULL) {
        goto loop_2;
    }
}
