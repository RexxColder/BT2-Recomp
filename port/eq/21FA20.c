#include "common.h"

extern void func_00206958(s32 a0, s32 a1);
extern void BtlAnim_SetNoBlend(s32 a0);
extern s32 func_002113C0(s32 a0, s32 a1, s32 a2, s32 a3);

s32 func_0021FA20(s32 obj) {
    func_00206958(obj, 0x20);
    BtlAnim_SetNoBlend(obj);
    func_002113C0(obj, 9, 0x200, 1);
    func_002113C0(obj, 1, 0x20000, 1);
    func_002113C0(obj, 0xE, 0x40, 1);
    func_002113C0(obj, 9, 0x20, 1);
    return 6;
}
