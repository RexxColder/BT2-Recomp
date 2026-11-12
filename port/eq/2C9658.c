#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002CBE18(u8 *arg0);
s32 func_002CC778(u8 *arg0);
void func_002C9700(u8 *arg0, u8 *arg1);

/* 0x002C9658(obj, out): copy the 44 bytes at obj+0xDF0 to out+0xC; when func_002CBE18(obj) is nonzero, out+0xE8 =
 * func_002CC778(obj); then the tail call func_002C9700(obj, out). */
void func_002C9658(u8 *arg0, u8 *arg1) {
    memcpy(arg1 + 0xC, arg0 + 0xDF0, 0x2C);
    if (func_002CBE18(arg0) != 0) {
        *(s32 *)(arg1 + 0xE8) = func_002CC778(arg0);
    }
    func_002C9700(arg0, arg1);
}
