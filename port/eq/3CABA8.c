#include "common.h"

extern u8 *D_00423114 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));
extern u32 D_3B0C34 __attribute__((section(".data")));

extern s32 func_003C6CC0(s32 packIndex);
extern s32 func_243968();
extern s32 func_003C8AA8();
extern s32 func_003C8AC8();
extern s32 func_297FE0();
extern s32 func_1018B8();
extern s32 func_2711A0();
extern s32 func_003C6770();
extern s32 func_28B090();
extern s32 func_28C0A8();
extern s32 func_297978();
extern s32 func_2438E8();
extern s32 func_003C8A48();
extern s32 func_003C7AE8();
extern s32 BattleSetup_Finish();
extern s32 func_003CA688();
extern s32 func_2437E8();
extern s32 func_271240();
extern s32 func_003CA360();
extern s32 ColorFade_IsFadingOut();
extern s32 func_101890();
extern s32 func_101498();
extern s32 ColorFade_IsOutDone();
extern s32 func_003C7A50();
extern s32 func_28B218();

/* 0x003CABA8: battle-setup main loop. Copies per-slot data from the ctx D_00423114 into D_3876A4 records (stride 0x20
 * from +0x90), runs the frame update chain, and on fade-out done with state 4 copies result blocks out. Returns 1. */
/* overlay asm 0x3CABD4: a0 untouched -> jal 3C6CC0 (pack index; 3CB1D0 passes 1). Was dropped: Dragon Tournament crash */
s32 func_003CABA8(s32 arg0) {
    s32 sp[4] __attribute__((aligned(16)));
    u8 *ctx;
    u8 *g;
    s32 i;
    s32 k;
    s32 done;

    sp[0] = 1;
    func_003C6CC0(arg0);
    func_243968(0, 0, 0);
    goto frame;

top:
    ctx = D_00423114;
    if (!(*(u32 *)(ctx + 0x18C) & 0x400)) {
        if (*(s32 *)(ctx + 0x36EC) != 0) goto frame;
        func_003C8AC8(sp);
        goto frame;
    }
    if (*(u32 *)(ctx + 0x18C) & 0x100000) {
        func_003C8AA8();
        if (!(0 < *(s32 *)(D_00423114 + 0x3640))) goto frame;
        for (i = 0;;) {
            ctx = D_00423114;
            g = D_3876A4;
            *(u16 *)(g + 0x90 + i * 0x20 + 0x12) = *(u16 *)(ctx + i * 4 + 0x3648);
            ctx = D_00423114;
            g = D_3876A4;
            *(u16 *)(g + 0x90 + i * 0x20 + 0x14) = *(u16 *)(ctx + 0x36C0 + i * 4 + 8);
            ctx = D_00423114;
            g = D_3876A4;
            *(u16 *)(g + i * 0x20 + 0xB8) = *(u16 *)(ctx + i * 4 + 0x3688);
            g = D_3876A4;
            *(u16 *)(g + 0x90 + i * 0x20 + 0x16) = (u16)i;
            g = D_3876A4;
            *(u16 *)(g + 0x90 + i * 0x20 + 0x10) |= 1;
            ctx = D_00423114;
            if (*(s32 *)(ctx + i * 4 + 0x3668) != 0) {
                g = D_3876A4;
                *(u16 *)(g + 0x90 + i * 0x20 + 0x10) |= 0x20;
                for (k = 0; k < 7; k++) {
                    u8 *c = D_00423114;
                    s32 a0 = *(s32 *)(c + 8 + 0x36C0 + i * 4);
                    s32 v1 = *(s32 *)(c + 8 + 0x36A0 + i * 4);
                    g = D_3876A4;
                    *(u16 *)(g + 0x90 + i * 0x20 + k * 2 + 0x1A) =
                        *(u16 *)(c + 0x3B10 + k * 4 + 0x1400 + a0 * 34 + (v1 << 14) + 0x10);
                }
            }
            ctx = D_00423114;
            if (*(u32 *)(ctx + 0x18C) & (0x200000u << i)) {
                g = D_3876A4;
                *(u16 *)(g + 0x90 + i * 0x20 + 0x10) |= 0x10;
            }
            ctx = D_00423114;
            i++;
            if (!(i < *(s32 *)(ctx + 0x3640))) break;
        }
        goto frame;
    }
    if (D_3B0C34 & 0x4000) {
        func_297FE0(0, 1, 0x40, 0x40, 1);
        *(u32 *)(D_00423114 + 0x18C) |= 0x100000;
    }
    if (func_1018B8() != 5) goto frame;
    *(u32 *)(D_00423114 + 0x18C) |= 0x100000;

frame:
    func_2711A0();
    func_003C6770();
    func_28B090();
    func_28C0A8();
    func_297978();
    func_2438E8();
    func_003C8A48();
    func_003C7AE8();
    BattleSetup_Finish();
    func_003CA688();
    func_2437E8();
    func_271240();
    ctx = D_00423114;
    if (*(u32 *)(ctx + 0x18C) & 0xC000) {
        if (*(s32 *)(ctx + 0x362C) != 4) goto frame;
        func_003CA360();
        goto frame;
    }
    if (ColorFade_IsFadingOut()) {
        func_101890();
        func_101498();
        goto frame;
    }
    done = ColorFade_IsOutDone();
    if (done == 0) goto top;
    ctx = D_00423114;
    if (*(s32 *)(ctx + 0x362C) != 4) goto frame;

    __builtin_memcpy(D_387F2C, ctx + 0x3B18, 0x4000);
    ctx = D_00423114;
    __builtin_memcpy(*(u8 **)(D_3876A4 + 0x4D0), ctx + 0x8F20, 0xB28);
    ctx = D_00423114;
    __builtin_memcpy(*(u8 **)(D_3876A4 + 0x4D4), ctx + 0x9A48, 0x90C);
    *(s32 *)(D_3876A4 + 0x4C8) = 0;
    *(s32 *)(D_3876A4 + 0x4CC) = 0;
    func_003C7A50();
    func_28B218();
    return sp[0];
}
