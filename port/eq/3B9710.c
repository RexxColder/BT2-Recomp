#include "common.h"

extern u8 *D_004213B0 __attribute__((section(".data")));
extern u8 *D_3876A0 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_3B0B00[] __attribute__((section(".data")));
extern u8 D_00421B58[] __attribute__((section(".data")));
extern u8 D_00421B68[] __attribute__((section(".data")));
extern u8 D_00421B78[] __attribute__((section(".data")));

s32 rand(void);
s32 func_26EB60(u8 *p);
void func_26EB78(u8 *arg0, u8 *arg1);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_29C7E0(s32 arg0);
void func_29C810(s32 arg0);
void func_29C7C0(s32 arg0);
void func_29C550(s32 arg0);
void func_29C820(s32 arg0);
s64 GetTimerSystemTime(void);
void func_325370(s64 arg0);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_24AF50(s32 a0);
u8 *func_101A88(s32 a0);
void func_101A10(u8 *a0, void *a1);
void func_101AB0(s32 a0, s32 a1, s32 a2, s32 a3);
void func_101A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1);
void func_101AF8();

void func_003B9710(s32 *s2p) {
    u8 *obj;
    u8 *P;
    u8 *E;
    u8 *a0v;
    u8 *s5;
    s32 st50[2];
    s32 st60[2];
    s32 s3 = 0;
    s32 s4 = 0;
    s32 v1;
    s32 a2;
    s32 i;
    s32 flags;
    s32 t;
    s32 r2;

    obj = D_004213B0;
    flags = *(s32 *)(obj + 0xCC);

    if (flags & 0x8) {
        if (func_26EB60(obj + 0x38) == 0) {
            return;
        }
        if (*(s32 *)(D_3B0B00 + 0x144) & 0x10) {
            *(s32 *)(D_004213B0 + 0x4518) = 0;
            func_26EB78(D_004213B0 + 0x38, D_00421B58);
            *(s32 *)(D_004213B0 + 0xCC) |= 0x10;
            func_297FE0(0, 0, 0x40, 0x40, 1);
        } else if (*(s32 *)(D_3B0B00 + 0x144) & 0x40) {
            *(s32 *)(D_004213B0 + 0x4518) = 0;
            func_26EB78(D_004213B0 + 0x38, D_00421B58);
            *(s32 *)(D_004213B0 + 0xCC) |= 0x20;
            func_297FE0(0, 0, 0x40, 0x40, 1);
        } else if (*(s32 *)(D_3B0B00 + 0x134) & 0x4000) {
            *(s32 *)(D_004213B0 + 0x4518) = 0;
            *s2p = 0;
            if (*(s32 *)(D_004213B0 + 0xD0) == 2) {
                *(s32 *)(D_004213B0 + 0xCC) |= 0x1;
                *(s32 *)(D_004213B0 + 0xCC) |= 0x2;
                *(s32 *)(D_004213B0 + 0xDC) = 0xF;
            } else {
                if (*(s32 *)(D_004213B0 + 0xD0) != 0) {
                    *(s32 *)(D_004213B0 + 0xE8) = 0xC;
                } else {
                    *(s32 *)(D_004213B0 + 0xE8) =
                        (*(s32 *)(D_3876A4 + 0x18) & 0x808) ? 7 : 0x12;
                }
                func_29C7E0(1);
                func_29C810(0);
                func_29C7C0(1);
                func_29C550(0);
                func_29C820(1);
            }
            func_297FE0(0, 1, 0x40, 0x40, 1);
        }
    } else if (flags & 0x4) {
        if (*(s32 *)(D_3B0B00 + 0x134) & 0x8) {
            *(s32 *)(D_004213B0 + 0x4518) = 0;
            func_26EB78(D_004213B0 + 0x38, D_00421B68);
            *(s32 *)(D_004213B0 + 0xCC) |= 0x8;
            func_297FE0(2, 3, 0x40, 0x40, 1);
            *(s32 *)(D_004213B0 + 0xD8) += 1;
            func_2493C0(0, 0x36DC, 0x3AF5, 0, *(s32 *)(D_004213B0 + 0xD8));
        }
    } else {
        *(s32 *)(D_004213B0 + 0x4518) = 0;
        if (*(s32 *)(D_3B0B00 + 0x134) & 0x8) {
            func_26EB78(D_004213B0 + 0x10, D_00421B78);
            func_26EB78(D_004213B0 + 0x38, D_00421B78);
            *(s32 *)(D_004213B0 + 0xCC) |= 0x4;
        }
        if (func_26EB60(D_004213B0 + 0x38)) {
            *(s32 *)(D_004213B0 + 0xCC) |= 0x4;
        }
    }

    /* L99D8: frame counter */
    v1 = *(s32 *)(D_004213B0 + 0x4518) + 1;
    *(s32 *)(D_004213B0 + 0x4518) = v1;
    if (v1 < 0x709) {
        return;
    }

    t = (s32)GetTimerSystemTime();
    func_325370((s64)t);

    v1 = *(s32 *)(D_3876A4 + 0x24);
    if (v1 >= 2 || v1 < 0) {
        *s2p = 2;
        *(s32 *)(D_3876A4 + 0x24) = 0;
    } else {
        do {
            a2 = rand() % *(s32 *)(D_004213B0 + 0x45C4);
        } while (a2 == *(s32 *)(D_3876A4 + 0x20));
        *(s32 *)(D_3876A4 + 0x20) = a2;

        if (a2 == 3) {
            st50[0] = 7;
            st50[1] = 0x2C;
            P = *(u8 **)(D_004213B0 + 0x45C0);
            st60[0] = *(s32 *)(P + 0x50);
            st60[1] = *(s32 *)(P + 0x54);
            P = P + 0x48;
            v1 = *(s32 *)(P + 0x10);
            s4 = *(s32 *)(P + 0x14);
            a0v = D_004213B0;
        } else if (a2 == 2) {
            P = *(u8 **)(D_004213B0 + 0x45C0);
            st50[0] = *(s32 *)(P + 0x90);
            st50[1] = *(s32 *)(P + 0x94);
            st60[0] = *(s32 *)(P + 0x98);
            st60[1] = *(s32 *)(P + 0x9C);
            v1 = *(s32 *)(P + 0xA0);
            s4 = *(s32 *)(P + 0xA4);
            a0v = D_004213B0;
        } else if (a2 == 4) {
            P = *(u8 **)(D_004213B0 + 0x45C0);
            st50[0] = 0x22;
            st60[0] = 1;
            st50[1] = *(s32 *)(P + 0x64);
            st60[1] = *(s32 *)(P + 0x6C);
            P = P + 0x60;
            v1 = *(s32 *)(P + 0x10);
            s4 = *(s32 *)(P + 0x14);
            a0v = D_004213B0;
        } else {
            P = *(u8 **)(D_004213B0 + 0x45C0);
            E = P + a2 * 24;
            st50[0] = *(s32 *)(E + 0x0);
            st50[1] = *(s32 *)(E + 0x4);
            st60[0] = *(s32 *)(E + 0x8);
            st60[1] = *(s32 *)(E + 0xC);
            v1 = *(s32 *)(E + 0x10);
            s4 = *(s32 *)(E + 0x14);
            a0v = E;
        }

        s3 = v1 - 1;
        *s2p = 1;
        *(s32 *)(D_3876A4 + 0x24) += 1;

        /* big block: *s2p == 1 */
        s5 = *(u8 **)(D_3876A0 + 0x74);
        func_101A10(a0v, &D_004213B0);
        *(s32 *)(D_3876A0 + 0x4D8) = 0;
        *(s32 *)(D_3876A0 + 0x4DC) = 0;
        func_101AB0(0, 1, 1, 0);
        func_101AB0(1, 1, 1, 0);
        for (i = 0; i < 2; i++) {
            u8 *b = func_101A88(i);
            s32 a2i = st50[i];
            u8 *t4 = s5 + a2i * 16;
            func_101AF8(b + 8, a2i * 9 + st60[i], 0, 2, 0, 0, 1, 1,
                        1, 1, 1, 1, 1, 1, 0,
                        *(s32 *)t4, *(s32 *)t4, *(s32 *)(t4 + 4));
        }
        r2 = func_24AF50(s4);
        func_101A60(6, s3, 5, 3, 4, r2);
    }

    /* L9CFC */
    *(s32 *)(D_004213B0 + 0xCC) |= 0x1;
    *(s32 *)(D_004213B0 + 0xCC) |= 0x2;
    *(s32 *)(D_004213B0 + 0xDC) = 0xF;
}
