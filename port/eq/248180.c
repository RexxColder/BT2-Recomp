#include "common.h"

extern s32 func_00325830(u8 *buf, const char *fmt, s32 n);
extern s32 func_0026EBC0(u8 *arg0, u8 *arg1, u8 *arg2);
extern s32 func_0026EC48(u8 *arg0, u8 *arg1, u8 *arg2);
extern s32 func_0026EFC8(u8 *arg0, u8 *arg1, s32 arg2);
extern s32 func_0026EA58(u8 *arg0);
extern s32 BattleSetup_Finish();
extern u8 *D_00387978;
extern char D_003746E0[];

static s32 PasswordCharIndex(s32 ch) {
    if (ch >= 'A' && ch <= 'Z') return ch - 'A';
    if (ch >= 'a' && ch <= 'z') return ch - 'a' + 26;
    switch (ch) {
    case '!': return 52;
    case '#': return 53;
    case '$': return 54;
    case '%': return 55;
    case '&': return 56;
    case '@': return 57;
    case '-': return 58;
    case '+': return 59;
    case '*': return 60;
    case '(': return 61;
    case ')': return 62;
    case '?': return 63;
    default: return 64;
    }
}

s32 func_00248180(void) {
    u8 sp[0x110];
    s32 i;
    s32 stop;
    s32 ch;
    s32 idx;

    if (*(s32 *)(D_00387978 + 0x40) == 0) {
        return (s32)D_00387978;
    }
    stop = 0;
    i = 0;
    do {
        func_00325830(sp + 0x10, D_003746E0, i);
        func_0026EBC0(D_00387978 + 4, sp + 0x10, sp);
        ch = *(s8 *)(*(u8 **)(D_00387978 + 0x40) + i);
        if (ch == 0) {
            stop = 1;
        }
        if (stop) {
            func_0026EFC8(D_00387978 + 4, sp, 8);
        } else {
            idx = PasswordCharIndex(ch);
            if (idx < 64) {
                func_0026EC48(D_00387978 + 4, sp, *(u8 **)(D_00387978 + 0x3C) + idx * 20);
                func_0026EFC8(D_00387978 + 4, sp, 4);
            } else {
                func_0026EFC8(D_00387978 + 4, sp, 8);
            }
        }
        i++;
    } while (i < 32);
    func_0026EA58(D_00387978 + 4);
    return BattleSetup_Finish();
}
