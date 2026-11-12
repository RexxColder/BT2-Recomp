#include "common.h"

s32 func_001D6A50(s32 arg0, s32 arg1);
s32 func_00129C28(s32 arg0, s32 arg1);
extern u8 *D_00387E9C;

void func_001D6AB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2) {
    s64 sp[2];
    s64 sp2[2];
    s32 s0;
    u8 *p;

    sp[0] = *(s64 *)(arg0 + 0);
    sp[1] = *(s64 *)(arg0 + 8);
    sp2[0] = *(s64 *)(arg1 + 0);
    sp2[1] = *(s64 *)(arg1 + 8);
    s0 = func_001D6A50(arg0, arg1);
    if (s0 == 0) {
        return;
    }
    func_00129C28(s0, (s32)sp);
    func_00129C28(s0 + 0x10, (s32)sp2);
    p = (u8 *)s0;
    *(f32 *)(p + 0x38) = farg0;
    *(f32 *)(p + 0x40) = farg2;
    *(s8 *)(p + 0x44) = -0x80;
    *(s8 *)(p + 0x49) = arg2 & 0xFF;
    *(s8 *)(p + 0x4A) = arg3 & 0xFF;
    *(s8 *)(p + 0x4B) = 1;
    *(f32 *)(p + 0x3C) = farg1 * 30.0f;
    *(s8 *)(p + 0x46) = -0x80;
    *(s8 *)(p + 0x45) = -0x80;
    *(s8 *)(p + 0x47) = 1;
    *(s8 *)(p + 0x48) = 0;
    *(s8 *)(p + 0x4C) = 0;
    *(s32 *)(D_00387E9C + 0x143C) = *(s32 *)(D_00387E9C + 0x143C) + 1;
}
