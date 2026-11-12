#include "common.h"

extern void *gBtlCamView;

void sceVu0RotTransPers(void *arg0, void *arg1, void *arg2, s32 arg3);
s32 func_003B5910(s32 arg0, s32 arg1, s32 arg2);
void func_003B6608();

/* 0x003B5FF8: projects four vectors (arg0..arg3) with sceVu0RotTransPers against gBtlCamView + 0x100 into frame words
 * sp+0x40, +0x50, +0x60, +0x70. If func_003B5910 rejects any of the four (x, y, z) triples the function returns.
 * Otherwise it builds four 16-byte blocks at sp+0x80..0xBF from f12..f19 (x, y, z = 1.0, w = 1.0 for each pair:
 * (f12, f13), (f14, f15), (f16, f17), (f18, f19)), four 4-word points at sp+0xC0..0xFF (xyz from the projected words,
 * w = 0) and calls func_003B6608(P0, P1, P2, P3, t0..t3, B0, B1, B2, B3, *(u64 *)(arg12 + 0x30), 1, arg11). */
void func_003B5FF8(void *arg0, void *arg1, void *arg2, void *arg3, s32 t0, s32 t1, s32 t2, s32 t3,
                   f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                   s32 arg9, s32 arg10, s32 arg11, void *arg12) {
    u8 sp[0x120];
    u64 d;

    sceVu0RotTransPers(sp + 0x40, (u8 *)gBtlCamView + 0x100, arg0, 1);
    sceVu0RotTransPers(sp + 0x50, (u8 *)gBtlCamView + 0x100, arg1, 1);
    sceVu0RotTransPers(sp + 0x60, (u8 *)gBtlCamView + 0x100, arg2, 1);
    sceVu0RotTransPers(sp + 0x70, (u8 *)gBtlCamView + 0x100, arg3, 1);

    if (func_003B5910(*(s32 *)(sp + 0x40), *(s32 *)(sp + 0x44), *(s32 *)(sp + 0x48)) != 0) {
        return;
    }
    if (func_003B5910(*(s32 *)(sp + 0x50), *(s32 *)(sp + 0x54), *(s32 *)(sp + 0x58)) != 0) {
        return;
    }
    if (func_003B5910(*(s32 *)(sp + 0x60), *(s32 *)(sp + 0x64), *(s32 *)(sp + 0x68)) != 0) {
        return;
    }
    if (func_003B5910(*(s32 *)(sp + 0x70), *(s32 *)(sp + 0x74), *(s32 *)(sp + 0x78)) != 0) {
        return;
    }

    *(f32 *)(sp + 0x80) = f12;
    *(f32 *)(sp + 0x84) = f13;
    *(f32 *)(sp + 0x88) = 1.0f;
    *(f32 *)(sp + 0x8C) = 1.0f;
    *(f32 *)(sp + 0x90) = f14;
    *(f32 *)(sp + 0x94) = f15;
    *(f32 *)(sp + 0x98) = 1.0f;
    *(f32 *)(sp + 0x9C) = 1.0f;
    *(f32 *)(sp + 0xA0) = f16;
    *(f32 *)(sp + 0xA4) = f17;
    *(f32 *)(sp + 0xA8) = 1.0f;
    *(f32 *)(sp + 0xAC) = 1.0f;
    *(f32 *)(sp + 0xB0) = f18;
    *(f32 *)(sp + 0xB4) = f19;
    *(f32 *)(sp + 0xB8) = 1.0f;
    *(f32 *)(sp + 0xBC) = 1.0f;

    *(s32 *)(sp + 0xC0) = *(s32 *)(sp + 0x40);
    *(s32 *)(sp + 0xC4) = *(s32 *)(sp + 0x44);
    *(s32 *)(sp + 0xC8) = *(s32 *)(sp + 0x48);
    *(s32 *)(sp + 0xCC) = 0;
    *(s32 *)(sp + 0xD0) = *(s32 *)(sp + 0x50);
    *(s32 *)(sp + 0xD4) = *(s32 *)(sp + 0x54);
    *(s32 *)(sp + 0xD8) = *(s32 *)(sp + 0x58);
    *(s32 *)(sp + 0xDC) = 0;
    *(s32 *)(sp + 0xE0) = *(s32 *)(sp + 0x60);
    *(s32 *)(sp + 0xE4) = *(s32 *)(sp + 0x64);
    *(s32 *)(sp + 0xE8) = *(s32 *)(sp + 0x68);
    *(s32 *)(sp + 0xEC) = 0;
    *(s32 *)(sp + 0xF0) = *(s32 *)(sp + 0x70);
    *(s32 *)(sp + 0xF4) = *(s32 *)(sp + 0x74);
    *(s32 *)(sp + 0xF8) = *(s32 *)(sp + 0x78);
    *(s32 *)(sp + 0xFC) = 0;

    d = *(u64 *)((u8 *)arg12 + 0x30);
    func_003B6608(sp + 0xC0, sp + 0xD0, sp + 0xE0, sp + 0xF0, t0, t1, t2, t3,
                  sp + 0x80, sp + 0x90, sp + 0xA0, sp + 0xB0, d, 1, arg11);
}
