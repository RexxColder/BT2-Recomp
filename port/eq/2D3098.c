#include "common.h"

void func_002D3178(u8 *arg0);
void func_002D3828(s32 arg0, s32 arg1, s32 arg2);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_002D3098(u8 *arg0) {
    memset(arg0, 0, 0x1C0);
    *(s32 *)(arg0 + 0xC) = 1;
    *(s32 *)(arg0 + 0x10) = 0xA;
    *(s32 *)(arg0 + 0) = 1;
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 8) = 0;
    func_002D3178(arg0);
    *(s64 *)(arg0 + 0x108) = 0;
    *(s64 *)(arg0 + 0x130) = 1;
    *(s64 *)(arg0 + 0x138) = 0x412B;
    *(s64 *)(arg0 + 0x148) = 0x30D40;
    *(s64 *)(arg0 + 0x170) = 0xF4240;
    *(s64 *)(arg0 + 0x178) = -1;
    *(s32 *)(arg0 + 0x1B8) = 0;
    *(s64 *)(arg0 + 0x110) = 1;
    *(s64 *)(arg0 + 0x118) = 0;
    *(s64 *)(arg0 + 0x120) = 1;
    *(s64 *)(arg0 + 0x128) = 0;
    *(s64 *)(arg0 + 0x140) = 0xF4240;
    *(s64 *)(arg0 + 0x150) = 0xF4240;
    *(s64 *)(arg0 + 0x158) = 0;
    *(s64 *)(arg0 + 0x160) = 0xF4240;
    *(s64 *)(arg0 + 0x168) = 0;
    *(s64 *)(arg0 + 0x180) = 0;
    *(s64 *)(arg0 + 0x188) = 0;
    *(s32 *)(arg0 + 0x190) = 0;
    *(s32 *)(arg0 + 0x194) = 0;
    *(s32 *)(arg0 + 0x198) = 0;
    *(s32 *)(arg0 + 0x19C) = 0;
    *(s32 *)(arg0 + 0x1A0) = 0;
    *(s32 *)(arg0 + 0x1A4) = 0;
    *(s32 *)(arg0 + 0x1A8) = 0;
    *(s32 *)(arg0 + 0x1AC) = 0;
    *(s32 *)(arg0 + 0x1B0) = 0;
    *(s32 *)(arg0 + 0x1B4) = 0;
    func_002D3828(0x412B, 0x30D40, -1);
}
