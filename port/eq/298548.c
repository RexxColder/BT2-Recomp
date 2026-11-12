#include "common.h"

extern s32 D_0038B058 __attribute__((section(".data")));

void func_00298548(s32 arg0, s32 arg1) {
    s32 base;
    s32 t4;
    s32 v0;
    s32 a3;
    s32 t1;
    s32 t0;
    s32 t2;
    s32 a2;
    s32 t3;
    s32 p;
    s32 rec0;
    s32 rec1;
    u16 flag;

    base = (s32)&D_0038B058;
    t4 = arg0 * 0x38;
    v0 = arg0 * 0x1C;
    a3 = base + 4;
    t1 = v0 + 0x50 + base;
    t0 = v0 + 0x60 + a3;
    flag = *(u16 *)t1;
    t2 = v0 + 0x64 + a3;
    a2 = (arg0 * 4) + base;
    t3 = arg1 * 0x38;
    if (!(flag & 1)) {
        *(u16 *)t1 = (u16)(flag | 1);
        p = *(s32 *)(base + 0x20);
        rec0 = p + t4;
        rec1 = p + t3;
        *(f32 *)t0 = (f32)(*(s32 *)(rec1 + 0x74) - *(s32 *)(rec0 + 0x234));
        *(f32 *)t2 = (f32)(*(s32 *)(rec1 + 0x78) - *(s32 *)(rec0 + 0x238));
        *(f32 *)t0 = *(f32 *)t0 / (30.0f / *(f32 *)(a2 + 0x8C));
        *(f32 *)t2 = *(f32 *)t2 / (30.0f / *(f32 *)(a2 + 0x8C));
        *(u16 *)(t1 + 4) = (u16)arg1;
        *(s32 *)(*(s32 *)(base + 0x20) + t4 + 0x230) = 1;
    }
}
