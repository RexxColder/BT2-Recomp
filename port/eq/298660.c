#include "common.h"

extern u8 D_0038B058[] __attribute__((section(".data")));

void func_00298660(s32 arg0, s16 arg1) {
    u8 *B;
    u8 *fl;
    u8 *P;
    f32 *t0;
    f32 *t1;
    f32 scale;
    s32 t3;
    s32 t4;
    s32 v0;
    u16 v1;

    B = D_0038B058;
    t4 = arg0 * 0x38;
    v0 = arg0 * 0x1C;
    t0 = (f32 *)(B + 4 + v0 + 0x60);
    t1 = (f32 *)(B + 4 + v0 + 0x64);
    fl = B + v0 + 0x50;
    v1 = *(u16 *)fl;
    scale = *(f32 *)(B + arg0 * 4 + 0x8C);
    t3 = arg1 * 0x38;
    if (!(v1 & 1)) {
        *(u16 *)fl = (u16)(v1 | 1);
        P = *(u8 **)(B + 0x20);
        *t0 = (f32)(*(s32 *)(P + t3 + 0x74) - *(s32 *)(P + t4 + 0x234));
        *t1 = (f32)(*(s32 *)(P + t3 + 0x78) - *(s32 *)(P + t4 + 0x238));
        *t0 = *t0 / (30.0f / scale);
        *t1 = *t1 / (30.0f / scale);
        *(s16 *)(fl + 4) = arg1;
        *(s32 *)(P + t4 + 0x230) = 1;
        *t0 = -*t0;
        *t1 = -*t1;
        *(u16 *)fl = (u16)(*(u16 *)fl | 4);
    }
}
