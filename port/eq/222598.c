#include "common.h"

s32 func_00217488(u8 *a0);
s32 func_00218838(u8 *a0, s32 a1);
void BattleSide_SetChara(u8 *a0, s32 a1);
void func_00212DD8(u8 *a0, s32 a1);
void func_0020FC38(u8 *a0, s32 a1);
void func_002100C0(u8 *a0, s32 a1);
void func_00206958(u8 *a0, s64 a1);
void func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);

/* 0x00222598: picks the side's character from the state word (0xA5..0xA8), then applies the
 * optional extras (sub-id, flags, 64-bit mask). The draft's switch is kept as is. */
void func_00222598(u8 *arg0) {
    s32 chara;
    s32 v;
    s64 mask;
    s32 sub3;
    s32 s4;
    s32 s5;
    s32 s6;

    chara = 0;
    mask = 0;
    sub3 = -1;
    s4 = 0;
    s5 = -1;
    s6 = -1;
    v = func_00217488(arg0);
    switch (v) {
    case 0xA5:
        chara = (func_00218838(arg0, 0) == 0) ? 0xC8 : 0xC9;
        func_002113C0(arg0, 0x10, 0x08000000, 1);
        break;
    case 0xA8:
        sub3 = 1;
        chara = (func_00218838(arg0, 0) == 0) ? 0xDF : 0xE0;
        s6 = 0x25;
        s4 = 1;
        mask = (s64)0x8000 << 23;
        break;
    case 0xA6:
        s5 = 2;
        chara = (func_00218838(arg0, 0) == 0) ? 0xDB : 0xDC;
        mask = (s64)0x8000 << 22;
        s4 = 1;
        break;
    case 0xA7:
        sub3 = 0;
        chara = (func_00218838(arg0, 0) == 0) ? 0xDD : 0xDE;
        s5 = 3;
        mask = (s64)0x8000 << 22;
        s4 = 1;
        break;
    default:
        break;
    }
    BattleSide_SetChara(arg0, chara);
    if (sub3 >= 0) {
        func_00212DD8(arg0, sub3);
    }
    if (s6 >= 0) {
        func_0020FC38(arg0, s6);
    }
    if (s5 >= 0) {
        func_002100C0(arg0, s5);
    }
    if (mask != 0) {
        func_00206958(arg0, mask);
    }
    if (s4 != 0) {
        func_002113C0(arg0, 0, 2, 0);
    }
}
