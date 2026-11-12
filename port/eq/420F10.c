#include "common.h"

extern u8 *D_0042FD78 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_00430550[] __attribute__((section(".data")));
extern u8 D_00430560[] __attribute__((section(".data")));
extern u8 D_00430570[] __attribute__((section(".data")));
extern u8 D_00430580[] __attribute__((section(".data")));

void func_26EBC0(u8 *a0, u8 *a1, u8 *a2);
void func_26EC48(u8 *a0, u8 *a1, u8 *a2);
void func_26EEF8(u8 *a0, u8 *a1, f32 f);
void func_26EA58(u8 *a0);
void func_24A598(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3);

/* 0x00420F10: per-frame update of the object at P = D_0042FD78 (R = P + 0x40): flag-gated calls on P->0xB4 (bit 1 and
 * bit 8, float fields 0xE4/0xE8/0xEC) and a 2-entry loop over P + 0x18 + 0x28 * k. The frame buffer holds 4 words. */
void func_00420F10(void) {
    u8 frame[0x20];
    u8 *P = D_0042FD78;
    u8 *R = P + 0x40;
    s32 s1;
    s32 s2;
    s32 g;
    s32 t;

    func_26EBC0(R, D_00430550, frame);
    if (*(s32 *)(P + 0xB4) & 1) {
        func_24A598(R, frame, 0, 0, *(s32 *)(P + 0x8),
                    *(s32 *)(D_3876A4 + 0x30) * 5 + *(s32 *)(P + 0xB8) + 0xE7, 1, *(s32 *)(P + 0xB8));
    } else {
        func_24A598(R, frame, 0, 0, *(s32 *)(P + 0x8),
                    *(s32 *)(D_3876A4 + 0x30) * 5 + *(s32 *)(P + 0xB8) + 0xE8, 1, *(s32 *)(P + 0xB8));
    }

    if (*(s32 *)(P + 0xB4) & 8) {
        func_26EEF8(R, frame, *(f32 *)(P + 0xE4));
        if (*(s32 *)(P + 0xB4) & 8) {
            func_26EBC0(R, D_00430560, frame);
            func_26EEF8(R, frame, *(f32 *)(P + 0xEC));
            func_26EBC0(R, D_00430570, frame);
            func_26EEF8(R, frame, *(f32 *)(P + 0xE8));
        }
    }

    g = *(s32 *)(D_3876A4 + 0x30);
    t = ((g < 0 ? g + 7 : g) >> 3) * 8;
    *(s32 *)(frame + 0x10) = ((g - t) % 2) << 8;
    *(s32 *)(frame + 0x18) = *(s32 *)(frame + 0x10) + 0x100;
    *(s32 *)(frame + 0x14) = ((g - t) / 2) << 6;
    *(s32 *)(frame + 0x1C) = *(s32 *)(frame + 0x14) + 0x40;
    func_26EBC0(R, D_00430580, frame);
    func_26EC48(R, frame, frame + 0x10);

    s2 = 0;
    s1 = 1;
    do {
        s1 -= 1;
        func_26EA58(P + s2 + 0x18);
        s2 += 0x28;
    } while (s1 >= 0);
}
