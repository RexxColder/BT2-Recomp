#include "common.h"

void func_0019E4E0(f32 farg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_0019ECF0(f32 farg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern u8 *D_003877F8;

void func_0019F550(s32 arg0, s32 arg1) {
    s32 off;

    off = arg1 * 0x3F;
    func_0019E4E0(1.0f, *(s32 *)(D_003877F8 + 0x1E8), D_003877F8 + off + 0x28, arg1, arg0, 0);
    func_0019E4E0(1.0f, *(s32 *)(D_003877F8 + 0x1EC), D_003877F8 + off + 0x31, arg1, arg0, 0);
    func_0019ECF0(1.0f, *(s32 *)(D_003877F8 + 0x1F0), D_003877F8 + 0x3A, arg0, 0, *(s32 *)D_003877F8);
}
