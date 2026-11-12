#include "common.h"

s32 memcmp(void *arg0, void *arg1, u32 arg2);
void func_002F9468(u8 *arg0, u8 *arg1, s32 arg2);
void func_002F9798(u8 *arg0);
void func_002FABF0(u8 *arg0, s32 arg1);
void func_002FEB98(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002FEBB8(s32 arg0);
extern u8 D_00354E90[] __attribute__((section(".data")));
extern u8 D_00354EA0[] __attribute__((section(".data")));
extern u8 D_0037C698[] __attribute__((section(".data")));
extern u8 D_0037C6A0[] __attribute__((section(".data")));
extern u8 func_002F33F0[] __attribute__((section(".data")));
extern u8 func_002FD2B8[] __attribute__((section(".data")));
extern u8 func_00300DD0[] __attribute__((section(".data")));

void func_002F3408(u8 *arg0) {
    memcmp(D_00354E90, D_00354E90, 0x80);
    memcmp(D_00354EA0, D_00354EA0, 0xE8);
    func_002FABF0(func_002F33F0, 0);
    func_002F9468(D_0037C698, func_00300DD0, 0);
    func_002FABF0(func_002F33F0, 0);
    func_002F9468(D_0037C6A0, func_002FD2B8, 0);
    func_002F9798(D_0037C6A0);
    if (arg0 != NULL) {
        func_002FEB98(*(s32 *)(arg0 + 8), *(s32 *)(arg0 + 0xC), *(s32 *)(arg0 + 0x10), *(s32 *)(arg0 + 4));
        func_002FEBB8(*(s32 *)(arg0 + 0));
        return;
    }
    func_002FEB98(0, 0, 0, 0);
    func_002FEBB8(0);
}
