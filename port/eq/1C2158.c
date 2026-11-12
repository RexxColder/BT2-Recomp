#include "common.h"

/* GUESS arity: a1 (arg1) is passed through, a2 = -0x80 and a3 = 0x64 are set before the call */
void func_00129AB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 *D_00387898;

void func_001C2158(s32 arg0, s8 arg1) {
    u8 *base;
    u16 temp;

    base = (u8 *)arg0;
    *(s8 *)(base + 0) = arg1;
    *(s16 *)(base + 4) = 0x3C;
    *(s16 *)(base + 6) = -1;
    *(s8 *)(base + 0xF) = 0x64;
    *(s8 *)(base + 0x1B) = -0x80;
    *(s8 *)(base + 1) = 0;
    *(s8 *)(base + 2) = 0;
    *(s8 *)(base + 3) = 0;
    *(s32 *)(base + 8) = 0;
    *(s8 *)(base + 0xC) = 0;
    *(s8 *)(base + 0xD) = 0;
    *(s8 *)(base + 0xE) = 0x64;
    *(f32 *)(base + 0x10) = 1.0f;
    *(s32 *)(base + 0x14) = 0;
    *(s8 *)(base + 0x18) = -0x80;
    *(s8 *)(base + 0x19) = -0x80;
    *(s8 *)(base + 0x1A) = -0x80;
    *(f32 *)(base + 0x1C) = 1.0f;
    func_00129AB0(arg0 + 0x20, (s32)arg1, -0x80, 0x64);
    *(f32 *)(base + 0x2C) = 1.0f;
    *(s8 *)(base + 0xD0) = 0;
    *(s8 *)(base + 0xD1) = 0;
    *(u16 *)(base + 0xD2) = *(u16 *)(D_00387898 + 0x124);
    temp = *(u16 *)(D_00387898 + 0x124);
    if (temp > 0xFFFEU) {
        *(u16 *)(D_00387898 + 0x124) = 0;
        return;
    }
    *(u16 *)(D_00387898 + 0x124) = (u16)(temp + 1);
}
