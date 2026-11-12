#include "common.h"

extern s32 func_0010B080(void);
extern s32 func_0010B0A0(s32 arg0);
extern s32 func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_00113CB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_00113D80(s32 arg0, s32 arg1);
extern s32 func_00113B00(s32 arg0, s32 arg1, s32 arg2);
extern void func_00113B50(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_0020B020(s32 arg0);
extern void func_0010F630(s32 arg0, s32 arg1, f32 farg0, f32 farg1);
extern void func_001140A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 BtlRec_CallFlagged(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0036C7E8[];

s32 func_0010FBA0(u8 *base, s32 idx, s32 arg2) {
    u8 sp[0x30];
    u8 *obj;
    u8 *pl;
    u8 *hud;
    u8 *row;
    u8 *rowPrev;
    u8 *mark;
    s32 x;
    s32 bit;
    s32 fade;
    f32 v;
    u32 alpha;

    obj = (u8 *)func_0010B080();
    pl = base + idx * 0x750 + 0xD0;
    row = (u8 *)func_0010B0A0(idx);
    hud = row + 0x1E0;
    func_00114508((s32)hud, 2, 0, 0x14);
    func_00113CB8((s32)hud, 0, *(s32 *)(obj + 8), 4);
    if (*(f32 *)(pl + 0x24) > 0.0f) {
        __builtin_memcpy(row + 0x480, hud, 0x60);
        hud[0x2B7] = 0;
        hud[0x2B6] = 0xFF;
        hud[0x2B8] = 0;
        v = *(f32 *)(pl + 0x24) * 44.0f;
        if (v >= 2147483648.0f) {
            alpha = (u32)(s32)(v - 2147483648.0f) | 0x80000000U;
        } else {
            alpha = (u32)(s32)v;
        }
        hud[0x2B9] = alpha;
        *(s32 *)(hud + 0x2A0) |= 0x84;
    } else {
        *(s32 *)(hud + 0x2A0) = 0;
    }
    __builtin_memcpy(sp, D_0036C7E8, 0x14);
    if ((*(s32 *)(pl + 0x694) & 1) != 0) {
        __builtin_memcpy(hud + 0x6C, sp, 10);
        func_00113D80((s32)(hud + 0x60), 0);
        func_00113B00((s32)(hud + 0x60), 0x27, 0x26);
        x = *(s16 *)(hud + 0x68) - 0x14;
    } else {
        *(s32 *)(hud + 0x60) = 0;
        x = 0x27;
    }
    mark = pl + 0x70C;
    rowPrev = hud + 0x60;
    for (bit = 1; bit < 5; bit++) {
        if (((*(s32 *)(pl + 0x694) >> bit) & 1) != 0) {
            __builtin_memcpy(rowPrev + 0x6C, sp + 0xA, 10);
            func_00113D80((s32)(rowPrev + 0x60), 0);
            func_00113B00((s32)(rowPrev + 0x60), x, 0x26);
            *(s32 *)(mark - 4) = x;
            *(s32 *)mark = 0x26;
            x += 0x1C;
        } else {
            *(s32 *)(mark - 4) = -1;
            *(s32 *)mark = -1;
            *(s32 *)(rowPrev + 0x60) = 0;
        }
        mark += 8;
        rowPrev += 0x60;
    }
    if (*(f32 *)(pl + 4) != 0.0f && *(f32 *)(pl + 8) != 0.0f) {
        func_00113B50((s32)hud, 0, (s32)*(f32 *)(pl + 4), (s32)*(f32 *)(pl + 8));
    }
    if (func_0020B020(arg2) != 0) {
        fade = *(s32 *)(pl + 0x6FC) + 0x10;
        *(s32 *)(pl + 0x6FC) = fade;
        if (fade > 0x80) {
            *(s32 *)(pl + 0x6FC) = 0x80;
        }
    } else {
        fade = *(s32 *)(pl + 0x6FC) - 0x10;
        if (fade < 0) {
            fade = 0;
        }
        *(s32 *)(pl + 0x6FC) = fade;
    }
    fade = *(s32 *)(pl + 0x6FC);
    if (fade > 0) {
        func_0010F630((s32)(hud + 0x360), (s32)hud, (f32)fade * 0.0078125f, 1.0f);
    }
    if (idx == 1) {
        func_001140A8((s32)hud, 0, 1, 0, 0x14);
    }
    return BtlRec_CallFlagged((s32)hud, 1, 0x14);
}
