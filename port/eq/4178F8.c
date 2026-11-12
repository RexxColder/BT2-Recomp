#include "common.h"

extern u8 *D_0042BB7C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_3876A0 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));

void func_00412C18(s32 a0);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_2711A0(void);
void func_00412530(void);
void func_28B090(void);
void func_0028C0A8(void);
void func_297978(void);
void func_2438E8(void);
void func_00414CF0(void);
void func_00413D28(void);
void func_004173D8(void);
void func_2437E8(void);
void func_271240(void);
void func_00417030(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void func_101498(void);
void func_00414DE8(s32 *a0);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_00101A10(void);
void func_101AB0(s32 a0, s32 a1, s32 a2, s32 a3);
u8 *func_00101A88(s32 arg0);
s64 func_0024B010(u8 *a0, u8 *a1, u8 *a2, u8 *a3, s32 a4);
s32 func_0024B7F0(s32 arg0);
void func_00101AF8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, s32 arg13, s64 arg14, s32 arg15, s32 arg16, s32 arg17);
void func_00413C48(void);
void func_28B218(void);
void BattleSetup_Finish(void);

#define G (D_0042BB7C)
#define W(off) (*(s32 *)(G + (off)))

/* 0x004178F8: sibling of func_004115C0 (2 entries per side instead of 5, other G offsets); returns v68 */
s32 func_004178F8(s32 a0) {
    s32 v68 = 1;
    s32 tmp[8];    /* sp+0x50 */
    s32 o60[8];    /* sp+0x60 */
    s32 p74;       /* sp+0x84 */
    s32 i, j, k, q, t, mode;
    s32 s1, t8;
    s64 s5;

    func_00412C18(a0);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_00412530();
        func_28B090();
        func_0028C0A8();
        func_297978();
        func_2438E8();
        func_00414CF0();
        func_00413D28();
        BattleSetup_Finish();
        func_004173D8();
        func_2437E8();
        func_271240();
        if ((W(0x238) & 0xC000) != 0) {
            if (W(0x373C) == 4) func_00417030();
            continue;
        }
        if (ColorFade_IsFadingOut()) {
            if (v68) func_101498();
            continue;
        }
        if (ColorFade_IsOutDone()) {
            if (W(0x373C) == 4) break;
            continue;
        }
        t = W(0x238);
        if ((t & 0xC00) != 0xC00) {
            if (W(0x3768) == 0) func_00414DE8(&v68);
            continue;
        }
        if ((t & 0x400000) == 0) {
            W(0x238) = t | 0x400000;
            W(0x3738) = 1;
        }
        if (W(0x3738) != 0) continue;
        t = W(0x3748) - 1;
        W(0x3748) = t;
        if (t != -1) continue;
        func_243A80(0, 0, 0);
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                q = (i * 2 + j) * 4;
                t = i * 20 + j * 4;
                *(s32 *)(D_3876A4 + 0x390 + t) = W(0x23C + q) + W(0x24C + q) * 7;
                *(s32 *)(D_3876A4 + 0x3B8 + t) = W(0x2B4 + q);
                *(s32 *)(D_3876A4 + 0x430 + t) = W(0x2C4 + q);
                *(s32 *)(D_3876A4 + 0x408 + t) = W(0x25C + q);
            }
        }
    }

    if (v68 == 0) {
        *(s64 *)(D_3876A0 + 0x4D8) = 0;
    } else {
        p74 = *(s32 *)(D_3876A0 + 0x74);
        func_00101A10();
        *(s64 *)(D_3876A0 + 0x4D8) = 0;
        if (W(0x3740) == 1) *(s64 *)(D_3876A0 + 0x4D8) |= 2;

        for (i = 0; i < 2; i++) {
            if (W(0x29C + i * 4) > 0) {
                k = 0;
                do {
                    q = (i * 2 + k) * 4;
                    tmp[i * 2 + k] = W(0x2A4 + q) * 9 + W(0x2C4 + q);
                    k++;
                } while (k < W(0x29C + i * 4));
            }
        }

        mode = W(0x3740);
        if (mode == 1) {
            func_101AB0(0, W(0x29C), 0, 0);
            func_101AB0(1, W(0x2A0), 0, 0);
            *(s32 *)(D_3876A4 + 0x468) = W(0x4C28);
            *(s32 *)(D_3876A4 + 0x470) = W(0x8C28);
            *(s32 *)(D_3876A4 + 0x46C) = W(0x4C2C);
            *(s32 *)(D_3876A4 + 0x474) = W(0x8C2C);
        } else if (mode == 0) {
            func_101AB0(0, W(0x29C), 0, 0);
            func_101AB0(1, W(0x2A0), 1, 0);
        } else if (mode == 2) {
            func_101AB0(0, W(0x29C), 1, 0);
            func_101AB0(1, W(0x2A0), 1, 0);
        }

        for (i = 0; i < 2; i++) {
            u8 *base = func_00101A88(i);
            if (W(0x29C + i * 4) > 0) {
                k = 0;
                do {
                    q = (i * 2 + k) * 4;
                    if (W(0x2B4 + q) == 1) {
                        if (*(s32 *)(D_3876A4 + 0x4C8) != 0 && *(s32 *)(D_3876A4 + 0x4CC) != 0) {
                            u8 *s0 = *(u8 **)(D_3876A4 + 0x4C8 + i * 4);
                            t = W(0x23C + q) + W(0x24C + q) * 7;
                            s5 = func_0024B010(*(u8 **)(G + 0x375C), *(u8 **)(G + 0x3760), s0 + t * 34 + 0x1408,
                                               (u8 *)o60, 0x14);
                            t = W(0x23C + q) + W(0x24C + q) * 7;
                            s1 = *(s16 *)(s0 + t * 34 + 0x1426);
                        } else {
                            t = W(0x23C + q) + W(0x24C + q) * 7;
                            s5 = func_0024B010(*(u8 **)(G + 0x375C), *(u8 **)(G + 0x3760),
                                               D_387F2C + t * 34 + 0x1408, (u8 *)o60, 0x14);
                            t = W(0x23C + q) + W(0x24C + q) * 7;
                            s1 = *(s16 *)(D_387F2C + t * 34 + 0x1426);
                        }
                        t = func_0024B7F0(o60[0]);
                        t8 = *(s32 *)(p74 + (W(0x2A4 + q) << 4)) + t;
                    } else {
                        s5 = 0;
                        s1 = 0;
                        for (j = 7; j >= 0; j--) o60[j] = 1;
                        t8 = *(s32 *)(p74 + (W(0x2A4 + q) << 4));
                    }
                    func_00101AF8(base + 8 + k * 0x58, tmp[i * 2 + k], 0, *(s32 *)(D_387F2C + 0x810), s1,
                                  *(s32 *)(D_387F2C + i * 4 + 0x814) ^ 1, o60[0], o60[1], o60[2], o60[3], o60[4], o60[5],
                                  o60[6], o60[7], s5, t8, t8, *(s32 *)(p74 + (W(0x2A4 + q) << 4) + 4));
                    k++;
                } while (k < W(0x29C + i * 4));
            }
        }
    }

    if (W(0x3740) == 1) {
        __builtin_memcpy(D_387F2C, G + 0x3B94, 0x4000);
        __builtin_memcpy(*(u8 **)(D_3876A4 + 0x4D0), G + 0x8F9C, 0xB28);
        __builtin_memcpy(*(u8 **)(D_3876A4 + 0x4D4), G + 0x9AC4, 0x90C);
        *(s32 *)(D_3876A4 + 0x4C8) = 0;
        *(s32 *)(D_3876A4 + 0x4CC) = 0;
    }
    func_00413C48();
    func_28B218();
    return v68;
}
