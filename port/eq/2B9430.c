#include "common.h"

void func_002B94E0(s32 arg0, void *arg1);
s32 func_002B9558(s32 arg0, void *arg1);
s32 func_002B95F8(s32 arg0, s32 arg1);
s32 func_002B9648(s32 arg0);
void func_002B96A8(void *arg0, void *arg1);
void func_002B9778(void *arg0, void *arg1);
void func_002B9798(s32 arg0, void *arg1, void *arg2);
void func_002B97E0(s32 arg0, void *arg1);

void func_002B9430(s32 arg0, void *arg1, void *arg2) {
    u8 *a1 = (u8 *)arg1;
    u8 *a2 = (u8 *)arg2;

    *(s32 *)(a2 + 0) = func_002B9648(*(s32 *)(a1 + 8));
    func_002B96A8(arg1, arg2);
    func_002B9778(arg1, arg2);
    func_002B9798(arg0, arg1, arg2);
    func_002B97E0(arg0, arg2);
    *(s32 *)(a2 + 0x88) = *(s32 *)(a1 + 0x88);
    *(s32 *)(a2 + 0x8C) = *(s32 *)(a1 + 0x8C);
    *(s32 *)(a2 + 0x90) = func_002B9558(arg0, arg1);
    *(s32 *)(a2 + 0x94) = func_002B95F8(arg0, *(s32 *)(a1 + 0x30));
    func_002B94E0(arg0, arg1);
}
