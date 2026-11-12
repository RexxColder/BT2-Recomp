#include "common.h"

extern u8 *D_0042A578 __attribute__((section(".data")));
extern u8 D_3B0B00[] __attribute__((section(".data")));

s32 func_26EB60(u8 *a0);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);

/* 0x003F7CA8: input state step for the menu. X = D_0042A578 (func_26EB60(X + 0x88) gate, mode at X->0x198: 0 polls
 * the pad block D_3B0B00 (fields 0x134/0x144), 1 counts X->0x144 and polls again). Ends with func_297FE0(a0, a1, 0x40,
 * 0x40, 1) for the path taken. */
void func_003F7CA8(s32 *out) {
    u8 *X;
    u8 *D;
    s32 a0 = 0;
    s32 a1 = 0;

    X = D_0042A578;
    if (func_26EB60(X + 0x88) == 0) {
        return;
    }
    D = D_3B0B00;

    if (*(s32 *)(X + 0x198) == 0) {
        if (*(s32 *)(D + 0x144) & 0x80) {
            if (!(*(s32 *)(X + 0x13C) & 4)) {
                *(s32 *)(X + 0x1B0) = 0x3D;
                a0 = 2;
                a1 = 7;
                goto call;
            }
        }
        if (*(s32 *)(D + 0x144) & 0x20) {
            if (!(*(s32 *)(X + 0x13C) & 4)) {
                *(s32 *)(X + 0x1B0) = 0x29;
                a0 = 2;
                a1 = 7;
                goto call;
            }
        }
        if (*(s32 *)(D + 0x144) & 0x50) {
            if (!(*(s32 *)(X + 0x13C) & 4)) {
                *(s32 *)(X + 0x198) = 1;
                a0 = 0;
                a1 = 0;
                goto call;
            }
        }
        if (*(s32 *)(D + 0x134) & 0x4000) {
            if (!(*(s32 *)(X + 0x13C) & 4)) {
                *(s32 *)(X + 0x194) = 1;
                a0 = 0;
                a1 = 1;
                goto call;
            }
        }
        if (*(s32 *)(D + 0x134) & 0x1000) {
            if (!(*(s32 *)(X + 0x13C) & 4)) {
                func_243A80(0, 0, 0);
                *out = 0;
                a0 = 0;
                a1 = 2;
                goto call;
            }
        }
        return;
    }
    if (*(s32 *)(X + 0x198) != 1) {
        return;
    }

    if (*(s32 *)(D + 0x144) & 0x80) {
        *(s32 *)(X + 0x144) = *(s32 *)(X + 0x144) - 1;
        if (*(s32 *)(X + 0x144) < 0) {
            *(s32 *)(X + 0x144) = 2;
        }
        a0 = 0;
        a1 = 0;
        goto call;
    }
    if (*(s32 *)(D + 0x144) & 0x20) {
        *(s32 *)(X + 0x144) = *(s32 *)(X + 0x144) + 1;
        if (*(s32 *)(X + 0x144) >= 3) {
            *(s32 *)(X + 0x144) = 0;
        }
        a0 = 0;
        a1 = 0;
        goto call;
    }
    if (*(s32 *)(D + 0x144) & 0x50) {
        *(s32 *)(X + 0x198) = 0;
        a0 = 0;
        a1 = 0;
        goto call;
    }
    if (*(s32 *)(D + 0x134) & 0x4000) {
        *(s32 *)(X + 0x194) = 1; /* asm 0x3F7ECC: sw a0 = X->0x198 (== 1 on this path). Was X + 0x88 (GUESS): 3F7710's state
                                    machine on 0x194 never started and input stopped after picking a difficulty */
        a0 = 0;
        a1 = 1;
        goto call;
    }
    if (*(s32 *)(D + 0x134) & 0x1000) {
        func_243A80(0, 0, 0);
        *out = 0;
        a0 = 0;
        a1 = 2;
        goto call;
    }
    return;

call:
    func_297FE0(a0, a1, 0x40, 0x40, 1);
}
