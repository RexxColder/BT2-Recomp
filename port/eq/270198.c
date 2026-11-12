#include "common.h"

s32 Flash_CxformIdentity(s32 arg0);
void func_0026FBD0(s32 arg0);
s32 func_0026DEF0(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

s32 func_00270198(u8 *arg0) {
    memset(arg0, 0, 0x40);
    *(s32 *)(arg0 + 0x44) = 0;
    memset(arg0 + 0x48, 0, 0x60);
    func_0026FBD0((s32)(arg0 + 0x78));
    Flash_CxformIdentity((s32)(arg0 + 0x90));
    return func_0026DEF0((s32)(arg0 + 0xA8));
}
