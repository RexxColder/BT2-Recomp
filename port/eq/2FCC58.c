#include "common.h"

s32 func_002FCAC8(s32 a0, s32 a1, s32 a2, s32 a3);
void func_002EFAB8();
void func_0032F558(s32 a0, s32 a1);
void func_0032F698(s32 a0, s32 a1);
void *memset(void *arg0, s32 arg1, u32 arg2);
void func_002FCB88(void);
void func_002FCBA0(void);
extern u8 D_003553F0[] __attribute__((section(".data")));
extern u8 D_0037E1A8[] __attribute__((section(".data")));
extern u8 D_0037E1C8[] __attribute__((section(".data")));
extern u8 D_0037E1E8[] __attribute__((section(".data")));
extern u8 D_0037E200[] __attribute__((section(".data")));
extern u8 D_0037E218[] __attribute__((section(".data")));

void *func_002FCC58(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *s0;
    s32 v;
    s32 v1;

    if (arg1 & 0x3F) {
        func_002EFAB8((s32)D_0037E1A8, arg1, arg2, arg3);
        return NULL;
    }
    if (arg2 & 0x1F) {
        func_002EFAB8((s32)D_0037E1C8, arg1);
        return NULL;
    }
    if (arg3 & 0x3F) {
        func_002EFAB8((s32)D_0037E1E8, arg3);
        return NULL;
    }
    if ((u32)arg0 >= 0x10U) {
        func_002EFAB8((s32)D_0037E200, arg0);
        return NULL;
    }
    s0 = D_003553F0 + arg0 * 0x44;
    if (*(s8 *)s0 != 0) {
        return NULL;
    }
    v = func_002FCAC8(arg0, arg1, arg2, arg3);
    *(s32 *)(s0 + 4) = v;
    if (v == 0) {
        /* a1 is whatever func_002FCAC8 left in it: no argument is passed */
        func_002EFAB8((s32)D_0037E218, 0);
        return NULL;
    }
    v1 = arg3 - 0x40;
    *(s32 *)(s0 + 0x10) = v1;
    *(u32 *)(s0 + 0x1C) = (u32)arg3;
    *(s32 *)(s0 + 0x18) = arg2;
    *(s32 *)(s0 + 0x14) = (arg1 + v1) | 0x20000000;
    *(s32 *)(s0 + 8) = 0;
    *(s32 *)(s0 + 0xC) = arg1;
    *(s8 *)(s0 + 1) = 0;
    memset((void *)arg1, 0, (u32)v1);
    func_0032F558(*(s32 *)(s0 + 0xC), *(s32 *)(s0 + 0xC) + *(s32 *)(s0 + 0x10) + 0x3F);
    func_0032F698(*(s32 *)(s0 + 0xC), *(s32 *)(s0 + 0xC) + *(s32 *)(s0 + 0x10) + 0x3F);
    *(s32 *)(s0 + 0x28) = (s32)func_002FCBA0;
    *(s8 *)(s0 + 0) = 1;
    *(s32 *)(s0 + 0x24) = 0;
    *(s32 *)(s0 + 0x2C) = 0;
    *(s8 *)(s0 + 2) = 1;
    *(s32 *)(s0 + 0x20) = (s32)func_002FCB88;
    return s0;
}
