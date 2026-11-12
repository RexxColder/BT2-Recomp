#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void ColSphere_Set(s32 arg0, s32 arg1, f32 farg0);
s32 func_003126C8(s32 arg0, s32 arg1);
extern f32 D_00387208;

void func_00297228(u8 *arg0, s32 arg1, f32 farg0, f32 farg1) {
    f32 sp[4];
    f32 f1;
    f32 f0;

    memset(sp, 0, 0x10);
    sp[3] = 1.0f;
    memset(arg0, 0, 0x220);
    *(s32 *)arg0 = 1;
    ColSphere_Set((s32)(arg0 + 0x1F0), (s32)sp, farg0);
    func_003126C8((s32)(arg0 + 0x20), (s32)sp);
    *(f32 *)(arg0 + 0x1C) = 1.0f;
    f1 = farg0 * D_00387208;
    f1 = f1 * farg0;
    f1 = f1 * farg0;
    f1 = f1 * farg1;
    *(f32 *)(arg0 + 0x8) = f1;
    f0 = f1 * farg0;
    f0 = f0 * farg0;
    f0 = f0 + f0;
    f0 = f0 / 5.0f;
    f0 = f0 * 20.0f;
    *(f32 *)(arg0 + 0x18) = f0;
    *(f32 *)(arg0 + 0x10) = f0;
    *(f32 *)(arg0 + 0x14) = f0;
    *(s32 *)(arg0 + 0xE4) = arg1;
    *(s64 *)(arg0 + 0x1D0) = *(s64 *)(arg0 + 0x1F0);
    *(s64 *)(arg0 + 0x1D8) = *(s64 *)(arg0 + 0x1F8);
    *(s64 *)(arg0 + 0x1E0) = *(s64 *)(arg0 + 0x200);
    *(s64 *)(arg0 + 0x1E8) = *(s64 *)(arg0 + 0x208);
}
