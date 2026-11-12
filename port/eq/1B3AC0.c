#include "common.h"

void func_003126C8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void EftRay_Create(u8 *arg0);
extern f32 D_00384FC0;
extern f32 D_00384FC4;
extern void *memset(void *dst, s32 c, u32 n);

/* 0x001B3AC0 (EftRay_StartHit, name already in config/symbols/agent_C.txt): builds the 0x50-byte ray record on the stack
 * (arg2 and arg3 as floats at +0x48/+0x4C, arg0 at +0x3C, arg4 at +0x20, constants 0xC0, 0x70, 60.0, 0x24, 1), passes it to
 * func_003126C8(rec, arg1, 0x70, 0x24) and EftRay_Create(rec). */
void EftRay_StartHit(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    u8 rec[0x60];

    memset(rec, 0, 0x10);
    *(s32 *)(rec + 0x10) = 0xC0;
    *(s32 *)(rec + 0x14) = 0xC0;
    *(s32 *)(rec + 0x18) = 0xC0;
    *(s32 *)(rec + 0x1C) = 0x70;
    *(f32 *)(rec + 0x20) = arg4;
    *(f32 *)(rec + 0x24) = 60.0f;
    *(f32 *)(rec + 0x28) = D_00384FC0;
    *(f32 *)(rec + 0x2C) = D_00384FC4;
    *(f32 *)(rec + 0x30) = D_00384FC0;
    *(s32 *)(rec + 0x34) = 1;
    *(s32 *)(rec + 0x38) = 0x24;
    *(s32 *)(rec + 0x3C) = arg0;
    *(s32 *)(rec + 0x40) = 1;
    *(s32 *)(rec + 0x44) = 0;
    *(s32 *)(rec + 0x48) = (s32)(f32)arg2;
    *(s32 *)(rec + 0x4C) = (s32)(f32)arg3;
    rec[0x50] = 1;
    func_003126C8(rec, arg1, 0x70, 0x24);
    EftRay_Create(rec);
}
