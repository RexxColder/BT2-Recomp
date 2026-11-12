#include "common.h"

extern s32 D_00354EC4 __attribute__((section(".data")));

void func_002F2BD8(u8 *arg0, s32 arg1, s32 arg2);
void func_002F2280(u8 *arg0, s32 arg1);
void func_002F2220(u8 *arg0, s32 arg1, s32 arg2);
s32 func_002F1F10(u8 *arg0, s32 arg1);
void func_002F2108(u8 *arg0);
void func_002F1DD8(u8 *arg0);
void func_002F1C48(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F2000(u8 *arg0);
void func_002F4130(u8 *arg0, s32 arg1);

void func_002F4238(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_002F2BD8(*(u8 **)(arg0 + 8), (s32)*(s16 *)(arg0 + 0x3E) * 0x800, (s32)*(s16 *)(arg0 + 0x3C) * 0x800);
    func_002F2280(*(u8 **)(arg0 + 8), D_00354EC4);
    func_002F2220(*(u8 **)(arg0 + 8), 0, 0);
    func_002F1F10(*(u8 **)(arg0 + 8), 0);
    func_002F2108(*(u8 **)(arg0 + 8));
    func_002F1DD8(*(u8 **)(arg0 + 8));
    func_002F1C48(*(u8 **)(arg0 + 8), arg1, arg2, arg3, arg4);
    func_002F2000(*(u8 **)(arg0 + 8));
    func_002F4130(arg0, *(s32 *)(arg0 + 0x10));
}
