#include "common.h"

void sceVu0Normalize();
void sceVu0UnitMatrix();
void func_00312490(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0036C990[] __attribute__((section(".data")));

void func_00114598(u8 *arg0, s32 arg1, f32 *arg2) {
    f32 fa[4];
    f32 fb[4];
    f32 fc[4];
    s64 dhi;

    *(s64 *)&fa[0] = *(s64 *)(D_0036C990 + 0);
    dhi = *(s64 *)(D_0036C990 + 8);
    *(s64 *)&fa[2] = dhi;
    sceVu0Normalize((s32)fc, arg1, (s32)arg2, dhi);
    func_00312490((s32)fb, (s32)fc, (s32)fa);
    sceVu0Normalize((s32)fb, (s32)fb);
    sceVu0UnitMatrix((s32)arg0);

    *(f32 *)(arg0 + 0x00) = fb[0];
    *(f32 *)(arg0 + 0x04) = fc[0];
    *(f32 *)(arg0 + 0x08) = fa[0];
    *(f32 *)(arg0 + 0x10) = fb[1];
    *(f32 *)(arg0 + 0x14) = fc[1];
    *(f32 *)(arg0 + 0x18) = fa[1];
    *(f32 *)(arg0 + 0x20) = fb[2];
    *(f32 *)(arg0 + 0x24) = fc[2];
    *(f32 *)(arg0 + 0x28) = fa[2];

    *(f32 *)(arg0 + 0x30) = (fb[0] * arg2[0]) + (fb[1] * arg2[1]) + (fb[2] * arg2[2]);
    *(f32 *)(arg0 + 0x34) = (fc[0] * arg2[0]) + (fc[1] * arg2[1]) + (fc[2] * arg2[2]);
    *(f32 *)(arg0 + 0x3C) = 1.0f;
    *(f32 *)(arg0 + 0x38) = (fa[0] * arg2[0]) + (fa[1] * arg2[1]) + (fa[2] * arg2[2]);
}
