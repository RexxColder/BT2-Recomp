#include "common.h"

s32 func_00276AC8(void);
s32 func_00276D00(void);
s32 func_00272E88(void);
void func_001014E8(s32 arg0);
void func_00101508(s32 arg0);
void func_00101560(void);
void BtlEvent_EndInterrupt(void);
void func_00277078(void);
void func_00277090(void);
void func_00277160(void);
void func_002772C0(void);
void func_00277400(void);
void func_00277418(void);
void func_00277430(void);
void func_00277448(void);
void func_00277460(void);
void func_002777C8(s32 arg0);
void func_002778E0(s32 arg0);
void func_00277890(void);
void func_002779A8(void);
void func_00277A90(void);
extern s32 D_00388D68[] __attribute__((section(".data")));

/* 0x00277B80: clear the 32-byte state block D_00388D68, take the mode from func_00276AC8, and store the
   matching handler address at block + 0x1C (mode 0 and 8 differ: 0 is BtlEvent_EndInterrupt, 8 clears it).
   Mode 2 turns the flag on when func_00276D00 returns 1. After the switch, when a handler is set and
   func_00272E88 is not 0x9B5, func_00101508 runs with mode + 0x3E0B; else the block is cleared and
   func_001014E8(-0x3C0) and func_00101560 run. Modes outside 0..15 run only the error path. The asm
   returns a value on the bltz path (0) and a void callee's v0 on the others, so this is void. */
void func_00277B80(void) {
    u8 *p;
    s32 mode;
    s32 flag;

    p = (u8 *)&D_00388D68;
    __builtin_memset(p, 0, 32);

    mode = func_00276AC8();
    if (mode < 0) {
        return;
    }
    if (mode >= 16) {
        func_001014E8(-0x3C0);
        func_00101560();
        return;
    }

    flag = 0;
    switch (mode) {
    case 0:
        *(s32 *)(p + 0x1C) = (s32)BtlEvent_EndInterrupt;
        break;
    case 1:
        *(s32 *)(p + 0x1C) = (s32)func_00277078;
        break;
    case 2:
        *(s32 *)(p + 0x1C) = (s32)func_00277090;
        if (func_00276D00() == 1) {
            flag = 1;
        }
        break;
    case 3:
        *(s32 *)(p + 0x1C) = (s32)func_00277160;
        break;
    case 4:
        *(s32 *)(p + 0x1C) = (s32)func_002772C0;
        break;
    case 5:
        *(s32 *)(p + 0x1C) = (s32)func_00277400;
        break;
    case 6:
        *(s32 *)(p + 0x1C) = (s32)func_00277418;
        break;
    case 7:
        *(s32 *)(p + 0x1C) = (s32)func_00277430;
        break;
    case 8:
        *(s32 *)(p + 0x1C) = 0;
        break;
    case 9:
        *(s32 *)(p + 0x1C) = (s32)func_00277448;
        break;
    case 10:
        *(s32 *)(p + 0x1C) = (s32)func_00277460;
        break;
    case 11:
        *(s32 *)(p + 0x1C) = (s32)func_002777C8;
        break;
    case 12:
        *(s32 *)(p + 0x1C) = (s32)func_002778E0;
        break;
    case 13:
        *(s32 *)(p + 0x1C) = (s32)func_00277890;
        break;
    case 14:
        *(s32 *)(p + 0x1C) = (s32)func_002779A8;
        break;
    case 15:
        *(s32 *)(p + 0x1C) = (s32)func_00277A90;
        break;
    default:
        break;
    }

    if (flag == 1) {
        mode = 1;
    }

    if (func_00272E88() != 0x9B5 && *(s32 *)(p + 0x1C) != 0) {
        func_00101508(mode + 0x3E0B);
    } else {
        *(s32 *)(p + 0x1C) = 0;
        func_001014E8(-0x3C0);
        func_00101560();
    }
}
