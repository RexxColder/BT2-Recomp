#include "common.h"

extern u8 *D_00421C04 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));

void func_003BBEF8(s32 arg0, void *arg1);
void func_003BBFC8(void);
void func_28B218(void);
void func_2711A0(void);
void func_28B090(void);
void func_28BDA0(void);
void func_297978(void);
void func_2438E8(void);
void func_1009E0(s32 arg0);
void func_2437E8(void);
void func_2711E8(void);
void func_243AF8(s32 a0, s32 a1, s32 a2, s32 a3);
void func_2439E8(s32 a0, s32 a1, s32 a2, s32 a3);
void func_271A00(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s64 a5);
void func_277E70(s32 a0, s32 a1, s32 a2);
s32 Dma_AddZbuf(s32 arg0, s32 arg1);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
s32 ColorFade_IsInDone(void);

/* 0x003BC000: calls func_003BBEF8(a0, a1) first. If t1 != 0, a fade-out wait (repeat the 8-call block while
 * ColorFade_IsFadingOut() or !ColorFade_IsOutDone()). Then the setup for a3 (func_28B218, Dma_AddZbuf, func_271A00 with a
 * 64-bit tail constant, Dma_AddZbuf, func_2439E8). Then the main loop on D_00421C04 (O): O->0xC bit 0 is set once
 * ColorFade_IsInDone; while fading out it repeats; once out-done it runs func_003BBFC8 and func_28B218 and returns.
 * Until then, when O->0xC bit 0 is set, O->0x14 counts up to O->0x10 + 2 and then a func_243AF8 call with a
 * 0x1E or 0xF tail, gated by a2 and the flags word D_003B0B00 + 0x134 (bits 0x4008). t0 selects black or the
 * (0,0,0) color in those calls. */
void func_003BC000(s32 a0, void *a1, s32 a2, s32 a3, s32 t0, s64 t1) {
    u8 *o;

    func_003BBEF8(a0, a1);

    if (t1 != 0) {
        if (a3 == 0) {
            func_243AF8(0xFF, 0xFF, 0xFF, 0x1E);
        } else {
            func_243AF8(0, 0, 0, 0x1E);
        }
        do {
            func_2711A0();
            func_28B090();
            func_28BDA0();
            func_297978();
            func_2438E8();
            func_1009E0(1);
            func_2437E8();
            func_2711E8();
        } while (ColorFade_IsFadingOut() != 0 || ColorFade_IsOutDone() == 0);
    }

    if (a3 != 0) {
        func_28B218();
        Dma_AddZbuf(0xE0, 1);
        func_271A00(0x700, 0x720, 0x200, 0x1C0, 1, (s64)0x3F80000000000000LL);
        Dma_AddZbuf(0xE0, 0);
        func_2439E8(0, 0, 0, 0x1E);
    } else {
        func_28B218();
        Dma_AddZbuf(0xE0, 1);
        func_271A00(0x700, 0x720, 0x200, 0x1C0, 1, (s64)0x3F80000080FFFFFFLL);
        Dma_AddZbuf(0xE0, 0);
        func_2439E8(0xFF, 0xFF, 0xFF, 0x1E);
    }

    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_277E70(*(s32 *)(D_00421C04 + 0x8), 0, 0x80);
        func_1009E0(1);
        func_2437E8();
        func_2711E8();
        if (ColorFade_IsInDone() != 0) {
            *(s32 *)(D_00421C04 + 0xC) |= 1;
        }
        if (ColorFade_IsFadingOut() != 0) {
            continue;
        }
        if (ColorFade_IsOutDone() != 0) {
            break;
        }

        o = D_00421C04;
        if (*(s32 *)(o + 0xC) & 1) {
            *(s32 *)(o + 0x14) += 1;
            if (*(s32 *)(o + 0x14) >= *(s32 *)(o + 0x10) + 2) {
                if (t0 != 0) {
                    func_243AF8(0, 0, 0, 0x1E);
                } else {
                    func_243AF8(0xFF, 0xFF, 0xFF, 0x1E);
                }
            }
        }
        if (a2 != 0 && (*(s32 *)(D_003B0B00 + 0x134) & 0x4008) != 0) {
            if (t0 != 0) {
                func_243AF8(0, 0, 0, 0xF);
            } else {
                func_243AF8(0xFF, 0xFF, 0xFF, 0xF);
            }
        }
    }

    func_003BBFC8();
    func_28B218();
}
