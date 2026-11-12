#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
void func_002C32B0(u8 *arg0, u8 *arg1, s32, s32);
void func_002C0098(u8 *arg0, s32 arg1);
void func_002CF228(u8 *arg0);
void func_002C32C8(u8 *arg0);

/* 0x002BFFF8(obj, src, out, n): func_002C32B0(buf, src, s32, s32); out->+4 = n; copy the 0x18 bytes of src to obj;
 * func_002C0098(obj + 0x18, the word at src+0x10); obj->+0x20 = obj->+0x24 = 0; func_002CF228(obj + 0x28);
 * func_002C32C8(buf). */
void func_002BFFF8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    u8 buf[0x10];

    func_002C32B0(buf, arg1, arg2, arg3);
    *(s32 *)(arg2 + 4) = arg3;
    memcpy(arg0, arg1, 0x18);
    func_002C0098(arg0 + 0x18, *(s32 *)(arg1 + 0x10));
    *(s32 *)(arg0 + 0x20) = 0;
    *(s32 *)(arg0 + 0x24) = 0;
    func_002CF228(arg0 + 0x28);
    func_002C32C8(buf);
}
