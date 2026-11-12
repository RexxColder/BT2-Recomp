#include "common.h"

extern s32 func_0025FBA8();
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_001F9C90(u8 *obj) {
    func_0025FBA8(*(s32 *)(obj + 0x152C));
    *(s32 *)(obj + 0x8E0) = *(s32 *)(obj + 0x8EC);
    *(u32 *)(*(u8 **)(obj + 0x1530) + 0xAF0) &= ~0x20;
    *(u32 *)(*(u8 **)(obj + 0x1530) + 0xAF0) &= ~0x40;
    func_002113C0(obj, 2, 0x71, 0);
    func_002113C0(obj, 2, 2, 1);
}
