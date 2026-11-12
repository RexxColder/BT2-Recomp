#include "common.h"

void StgAabb_SetEmpty(s32 arg0, s64 arg1, s32 arg2, s64 arg3);
void ColBox_AddPointKeepW(s32 arg0, f32 *arg1);
extern u8 D_0036CC00[] __attribute__((section(".data")));
extern u8 D_0036CC10[] __attribute__((section(".data")));
extern u8 *gBtlStage;

void func_0011DCA8(s32 arg0, s32 arg1) {
    s64 sp[4];
    u8 *s0;

    s0 = (u8 *)((arg1 << 6) + (*(s32 *)(gBtlStage + 0x5C) + (*(s32 *)(gBtlStage + 0x3C) * 4)));
    sp[0] = *(s64 *)D_0036CC00;
    sp[1] = *(s64 *)(D_0036CC00 + 8);
    sp[2] = *(s64 *)D_0036CC10;
    sp[3] = *(s64 *)(D_0036CC10 + 8);
    StgAabb_SetEmpty(arg0, *(s64 *)D_0036CC00, (s32)D_0036CC10, *(s64 *)(D_0036CC00 + 8));
    *(f32 *)((u8 *)sp + 0x0) = *(f32 *)(s0 + 0x20) - *(f32 *)(s0 + 0x30);
    *(f32 *)((u8 *)sp + 0x8) = *(f32 *)(s0 + 0x28) - *(f32 *)(s0 + 0x38);
    *(f32 *)((u8 *)sp + 0x10) = *(f32 *)(s0 + 0x20) + *(f32 *)(s0 + 0x30);
    *(f32 *)((u8 *)sp + 0x18) = *(f32 *)(s0 + 0x28) + *(f32 *)(s0 + 0x38);
    ColBox_AddPointKeepW(arg0, (f32 *)sp);
    ColBox_AddPointKeepW(arg0, (f32 *)((u8 *)sp + 0x10));
}
