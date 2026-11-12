#include "common.h"

extern s32 func_0010B080(void);
extern s32 func_0010B090(void);
extern s32 func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_00106198(void);
extern void func_00113CB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_00112B60(s32 arg0, s32 arg1, void *arg2, void *arg3);
extern void func_00113D80(s32 arg0, s32 arg1);
extern void func_00113B50(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 BtlRec_CallFlagged(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003876A0;
extern u8 D_0036C688[];
extern u8 D_0036C6A8[];
extern u8 D_0036C70C[];
extern u8 D_0036C716[];

s32 func_0010D028(void) {
    u8 sp[0x30];
    u32 *divs = (u32 *)sp;
    u32 *div;
    u8 *obj;
    u8 *hud;
    u8 *row;
    u8 *glyph;
    s32 mask = 0;
    s32 value = -1;
    s32 digits = 3;
    s32 started = 0;
    s32 n;
    s32 q;
    s32 x;

    obj = (u8 *)func_0010B080();
    hud = (u8 *)(func_0010B090() + 0x7C80);
    __builtin_memcpy(sp, D_0036C688, 0x1C);
    func_00114508((s32)hud, 2, 0, 5);
    *(s32 *)(sp + 0x28) = 0;
    if (*(s32 *)(D_003876A0 + 0xC0) != 0) {
        value = func_00106198();
        *(s32 *)(sp + 0x28) = value;
        if (value < 100) {
            digits = 2;
            if (value < 10) {
                digits = 1;
                mask = 0x800000;
                if (value >= 4) {
                    mask = 0x400000;
                }
            }
        }
    }
    func_00113CB8((s32)hud, 1, *(s32 *)(obj + 8), 3);
    func_00112B60(*(s32 *)(obj + 8), 3, sp + 0x20, sp + 0x24);
    *(s16 *)(hud + 6) = 0;
    *(u16 *)(hud + 0xA) = *(u16 *)(sp + 0x24);
    if (value < 0) {
        __builtin_memcpy(hud + 0x6C, D_0036C70C, 10);
        func_00113D80((s32)(hud + 0x60), 0);
        func_00113B50((s32)(hud + 0x60), 0,
                      (0x200 - (*(s16 *)(D_0036C70C + 4) - *(s16 *)D_0036C70C)) >> 1, 5);
        BtlRec_CallFlagged((s32)hud, 1, 5);
        return 1;
    }
    if (digits > 0) {
        n = digits;
        div = divs + digits - 1;
        row = hud + 0x60;
        do {
            q = (u32)value / *div;
            if ((q != 0 || started == 0) && (n != 1 || *(s32 *)(sp + 0x28) != 0)) {
                if (q != 0) {
                    started = 1;
                    glyph = D_0036C6A8 + q * 10;
                    __builtin_memcpy(row + 0xC, glyph, 10);
                    value = value - q * *div;
                } else {
                    __builtin_memcpy(row + 0xC, D_0036C716, 10);
                }
            } else {
                __builtin_memcpy(row + 0xC, D_0036C6A8, 10);
            }
            func_00113D80((s32)row, 0);
            n--;
            div--;
            *(s32 *)row = mask | 1;
            row += 0x60;
        } while (n > 0);
    }
    if (digits == 2) {
        func_00113B50((s32)(hud + 0x60), 0, 0xE9, 4);
    } else if (digits == 3) {
        func_00113B50((s32)(hud + 0x60), 0, 0xE0, 4);
    } else if (digits == 1) {
        x = (0x200 - (*(s16 *)(D_0036C6A8 + 4) - *(s16 *)D_0036C6A8)) >> 1;
        func_00113B50((s32)(hud + 0x60), 0, x, 4);
    }
    func_00113B50((s32)(hud + 0xC0), 1, 0xF, 0);
    BtlRec_CallFlagged((s32)hud, 1, 5);
    return 1;
}
