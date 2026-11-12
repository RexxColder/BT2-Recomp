#include "common.h"

void func_0019E4E0(f32 f0, s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_0019ECF0(f32 f0, s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern u8 *D_003877F8;

void func_0019F3F0(s32 arg0, s32 arg1) {
    s32 off;

    off = arg1 * 0x3F;
    func_0019E4E0(1.0f, *(s32 *)(D_003877F8 + 0x1D0), (s32)(D_003877F8 + off + 0x28), arg1, arg0, 0);
    func_0019E4E0(1.0f, *(s32 *)(D_003877F8 + 0x1D4), (s32)(D_003877F8 + off + 0x31), arg1, arg0, 0);
    func_0019ECF0(1.0f, *(s32 *)(D_003877F8 + 0x1D8), (s32)(D_003877F8 + 0x3A), arg0, 0, *(s32 *)D_003877F8);
}
