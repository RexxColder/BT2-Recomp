#include "common.h"

void func_002837C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283800(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 D_00387B04;

void func_002824C8(void) {
    s32 s0;
    s32 s1;
    s32 base;

    s0 = 0;
    s1 = 0;
    do {
        base = D_00387B04 + s0;
        *(s32 *)(base + 0x00) = 0;
        *(s32 *)(base + 0x04) = 0;
        *(f32 *)(base + 0x08) = 1.0f;
        *(s32 *)(base + 0x0C) = 0;
        *(f32 *)(base + 0x10) = 2.0f;
        *(f32 *)(base + 0x14) = 2.0f;
        *(f32 *)(base + 0x18) = 2.0f;
        s0 += 0x30;
        *(u8 *)(base + 0x28) = 1;
        func_002837C0(s1, 0x80, 0x80, 0x80, 0);
        func_00283800(s1, 0x80, 0x80, 0x80, 0);
        func_00283840(s1, 0x80, 0x80, 0x80, 0);
        s1 += 1;
    } while (s1 < 2);
}
