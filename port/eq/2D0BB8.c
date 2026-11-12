#include "common.h"

void func_002D0DD8(s32 arg0, s32 arg1);
void func_002D0E20(s32 arg0);
void func_002D1C08(s32 arg0, s32 arg1, s32 arg2);
void func_002D1640(s32 arg0, s32 arg1, s32 arg2);
void func_002D1688(s32 arg0, s32 arg1, s32 arg2);
void func_002D16E8(s32 arg0, s32 arg1, s32 arg2);
void func_002D1708(s32 arg0, s32 arg1, s32 arg2);

void func_002D0BB8(s32 arg0, s32 arg1) {
    u8 *s1;
    u8 *p;
    s32 i;

    s1 = (u8 *)arg1;
    func_002D1C08(arg0, (s32)func_002D1640, 0);
    func_002D1C08(arg0, (s32)func_002D1688, 1);
    func_002D1C08(arg0, 0, 2);
    func_002D1C08(arg0, (s32)func_002D16E8, 3);
    func_002D1C08(arg0, 0, 4);
    func_002D1C08(arg0, (s32)func_002D1708, 5);

    *(s32 *)(s1 + 0x18) = 0;
    func_002D0E20(arg1 + 0x1C);
    func_002D0DD8(arg1 + 0xC0, 0);
    func_002D0DD8(arg1 + 0x3C, 0x7FFFFFFF);
    func_002D0DD8(arg1 + 0x68, -1);
    func_002D0DD8(arg1 + 0x94, -1);
    func_002D0DD8(arg1 + 0xEC, -1);
    func_002D0DD8(arg1 + 0x118, 0x7FFFFFFF);

    *(s32 *)(s1 + 0x144) = 0;
    *(s32 *)(s1 + 0x148) = 0;
    *(s32 *)(s1 + 0x160) = 0;
    *(s32 *)(s1 + 0x164) = 0;
    *(s32 *)(s1 + 0x168) = 0;
    *(s64 *)(s1 + 0x158) = -1;
    *(s64 *)(s1 + 0x150) = -1;
    /* 32 words zeroed downward from 0x1E8 */
    i = 0x1F;
    p = s1 + 0x1E8;
    do {
        i -= 1;
        *(s32 *)p = 0;
        p -= 4;
    } while (i >= 0);

    *(s32 *)(s1 + 0x1F0) = 0;
    *(s32 *)(s1 + 0x1F4) = 0;
    *(s32 *)(s1 + 0x1F8) = 0;
    *(s32 *)(s1 + 0x1EC) = 1;
    /* 32 words zeroed downward from 0x278 (a0 = s1 + 0xC, + 0x26C) */
    i = 0x1F;
    p = s1 + 0xC + 0x26C;
    do {
        i -= 1;
        *(s32 *)p = 0;
        p -= 4;
    } while (i >= 0);

    *(s32 *)(s1 + 0x2A8) = 0;
    *(s32 *)(s1 + 0x2CC) = -1;
    *(s32 *)(s1 + 0x2D8) = -5;
    *(s32 *)(s1 + 0x2A0) = 0x7FFFFFFF;
    *(s32 *)(s1 + 0x2DC) = 0;
    *(s32 *)(s1 + 0x2AC) = 0x3E8;
    *(s32 *)(s1 + 0x2E0) = 1;
    *(s32 *)(s1 + 0x2BC) = 0x64;
    *(f32 *)(s1 + 0x2C8) = -1.0f;
    *(s32 *)(s1 + 0x2D0) = *(s32 *)(s1 + 0x2A8);
    *(s32 *)(s1 + 0x5B8) = 0;
    *(s32 *)(s1 + 0x2E4) = -1;
    *(s32 *)(s1 + 0x27C) = -5;
    *(s32 *)(s1 + 0x280) = 1;
    *(s32 *)(s1 + 0x284) = -5;
    *(s32 *)(s1 + 0x288) = 1;
    *(s32 *)(s1 + 0x28C) = -1;
    *(s32 *)(s1 + 0x290) = 1;
    *(s32 *)(s1 + 0x294) = -5;
    *(s32 *)(s1 + 0x298) = 0x7FFFFFFF;
    *(s32 *)(s1 + 0x29C) = 0;
    *(s32 *)(s1 + 0x2A4) = 0;
    *(s32 *)(s1 + 0x2B0) = 0;
    *(s32 *)(s1 + 0x2B4) = 0;
    *(s32 *)(s1 + 0x2B8) = 1;
    *(f32 *)(s1 + 0x2C0) = -1.0f;
    *(s32 *)(s1 + 0x2C4) = 0;
    *(s32 *)(s1 + 0x2D4) = 0;
    *(s32 *)(s1 + 0x2E8) = 0;
    *(s32 *)(s1 + 0x5B0) = 0;
    *(s32 *)(s1 + 0x5B4) = 0;
}
