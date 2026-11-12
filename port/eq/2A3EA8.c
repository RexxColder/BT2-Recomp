#include "common.h"

extern u8 D_003B0F40[] __attribute__((section(".data")));

u8 *func_002A3E80(u8 *a0, s32 a1, s32 a2, s32 a3);
void func_002A42C8(s32 a0, s32 a1);
void func_002A4148(s32 a0, s32 a1, s32 a2, s32 a3);
void func_002A4420(s32 a0, s32 a1, s32 a2);
s32 func_002A47F0(s32 a0);
s32 func_002A47F8(s32 a0);
void func_002A4808(s32 a0, s32 a1);
u8 *func_002A4108(void);
void *memcpy(void *arg0, void *arg1, u32 arg2);

/* 0x002A3EA8: looks up a record r = func_002A3E80(...) and dispatches on its signed bytes at +1..+5;
 * the results go to D_003B0F40 (+0x1600, +0x1604). Returns s2 (1 unless func_002A47F8 ran). */
s32 func_002A3EA8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *r;
    u8 *p;
    s32 s0;
    s32 s2;
    s32 s3;
    s32 side;

    s0 = arg1;
    s2 = 1;
    s3 = 1;
    r = func_002A3E80(arg0, arg1, arg2, arg3);
    /* 0x2A3ED4: lb a0,3(s1) — el asm no lee r[6]; el fallback anterior era inventado. */
    side = *(s8 *)(r + 3);

    if (side >= 0) {
        func_002A42C8(side, s0);
        /* 0x2A3EE8-0x2A3EF8: lb a0,3(s1); lb a1,4(s1); lb a2,5(s1); move a3,s0 -> 2A4148(r[3], r[4], r[5], s0).
           El port pasaba (side, side, r[5]): con side=1 el retrato del free roam buscaba el slot 1, que no tiene
           layout (NULL) y el guard de 2A3C08 lo ocultaba; en la PS2 el slot es r[4] (=0, con layout). */
        func_002A4148(*(s8 *)(r + 3), *(s8 *)(r + 4), *(s8 *)(r + 5), s0);
        s0 = s0 - 0x25;
        *(s32 *)(D_003B0F40 + 0x1600) = *(s8 *)(r + 4);
        *(s32 *)(D_003B0F40 + 0x1604) = *(s8 *)(r + 3);
    } else {
        *(s32 *)(D_003B0F40 + 0x1604) = -1;
        *(s32 *)(D_003B0F40 + 0x1600) = -1;
    }

    if (*(s8 *)(r + 2) >= 0) {
        func_002A4420(*(s8 *)(r + 3), *(s8 *)(r + 2), s0);
        s0 = s0 - 0x25;
        s3 = func_002A47F0(s0);
        s2 = func_002A47F8(s0);
        if (s2 != 0) {
            func_002A4808(*(s8 *)(r + 3), s0);
        }
    }

    if (s3 != 0 && *(s8 *)(r + 1) >= 0) {
        p = func_002A4108();
        memcpy(r + 0x10, p, 0x58);
        *(u8 *)(r + 0xC) = 1;
    }
    return s2;
}
