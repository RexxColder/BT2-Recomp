#include "common.h"

void func_00129C28(s32 *arg0, u8 *arg1);
void func_001E70B0(f32 farg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void func_001E7208(s32 arg0, s32 arg1);
extern u8 *D_00387808;

void func_001A0390(u8 *arg0, s32 arg1, f32 farg0) {
    s32 sp[4];
    u8 *s1;
    u8 *s2;
    u8 *s0;

    s2 = D_00387808;
    s1 = *(u8 **)(arg0 + 0x38);
    func_00129C28(sp, s1 + 0x10);
    s0 = s1 + (arg1 << 2) + 0x2C;
    func_001E70B0(farg0, (s32)s0, *(s32 *)(s2 + 0x8 + 0x218), 0, 0, 1, (s32)sp, (s32)(s2 + 0x10), *(s32 *)s1);
    func_001E7208((s32)s0, 2);
}
