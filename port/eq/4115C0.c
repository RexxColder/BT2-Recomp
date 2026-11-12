#include "common.h"

extern u8 *D_0042BB78 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_3876A0 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));

void func_0040B440(s32 a0);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_2711A0(void);
void func_0040AC30(void);
void func_28B090(void);
void func_0028C0A8(void);
void func_297978(void);
void func_2438E8(void);
void func_0040D6A8(void);
void func_0040C530(void);
void BattleSetup_Finish(void);
s32 func_004110A0(void);
void func_2437E8(void);
void func_271240(void);
s32 func_00410C18(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsOutDone(void);
void func_101498(void);
void func_0040D7A0(s32 *a0);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_00101A10(void);
void func_101AB0(s32 a0, s32 a1, s32 a2, s32 a3);
u8 *func_00101A88(s32 arg0);
s64 func_0024B010(u8 *a0, u8 *a1, u8 *a2, u8 *a3, s32 a4);
s32 func_0024B7F0(s32 arg0);
void func_00101AF8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, s32 arg13, s64 arg14, s32 arg15, s32 arg16, s32 arg17);
void func_0040C480(s32 arg0);
void func_28B218(void);

#define G (D_0042BB78)
#define W(off) (*(s32 *)(G + (off)))

/* 0x004115C0: battle-setup menu main loop (returns v68, flag set to 1 at entry, cleared by func_0040D7A0) */
s32 func_004115C0(s32 a0) {
    s32 v68 = 1;
    s32 tmp[10];   /* sp+0x50 */
    s32 o80[8];    /* sp+0x80 */
    s32 p74;       /* sp+0xA4 */
    s32 i, j, k, idx, t, mode;
    s32 s1, s2;
    s64 s3;
    u8 *obj;

    func_0040B440(a0);
    func_243968(0, 0, 0);

    for (;;) {
        func_2711A0();
        func_0040AC30();
        func_28B090();
        func_0028C0A8();
        func_297978();
        func_2438E8();
        func_0040D6A8();
        func_0040C530();
        BattleSetup_Finish();
        func_004110A0();
        func_2437E8();
        func_271240();
        if ((W(0x240) & 0xC000) != 0) {
            if (W(0x37C4) == 4) func_00410C18();
            continue;
        }
        if (ColorFade_IsFadingOut()) {
            if (v68) func_101498();
            continue;
        }
        if (ColorFade_IsOutDone()) {
            if (W(0x37C4) == 4) break;
            continue;
        }
        t = W(0x240);
        if ((t & 0xC00) != 0xC00) {
            if (W(0x37E8) == 0) func_0040D7A0(&v68);
            continue;
        }
        if ((t & 0x400000) == 0) {
            W(0x240) = t | 0x400000;
            W(0x37C0) = 1;
        }
        if (W(0x37C0) != 0) continue;
        t = W(0x37D0) - 1;
        W(0x37D0) = t;
        if (t != -1) continue;
        func_243A80(0, 0, 0);
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 5; j++) {
                idx = i * 5 + j;
                *(s32 *)(D_3876A4 + 0x390 + idx * 4) = W(0x244 + idx * 4) + W(0x26C + idx * 4) * 7;
                *(s32 *)(D_3876A4 + 0x3B8 + idx * 4) = W(0x30C + idx * 4);
                *(s32 *)(D_3876A4 + 0x430 + idx * 4) = W(0x334 + idx * 4);
                *(s32 *)(D_3876A4 + 0x408 + idx * 4) = W(0x294 + idx * 4);
            }
        }
    }

    if (v68 == 0) {
        *(s64 *)(D_3876A0 + 0x4D8) = 0;
    } else {
        p74 = *(s32 *)(D_3876A0 + 0x74);
        func_00101A10();
        *(s64 *)(D_3876A0 + 0x4D8) = 0;
        if (W(0x37C8) == 1) *(s64 *)(D_3876A0 + 0x4D8) |= 2;

        for (i = 0; i < 2; i++) {
            if (W(0x2DC + i * 4) > 0) {
                k = 0;
                do {
                    idx = i * 5 + k;
                    tmp[idx] = W(0x2E4 + idx * 4) * 9 + W(0x334 + idx * 4);
                    k++;   /* B12: el asm original incrementa el contador (0x4118D8 addiu s4,s4,1) */
                } while (k < W(0x2DC + i * 4));
            }
        }

        mode = W(0x37C8);
        if (mode == 1) {
            func_101AB0(0, W(0x2DC), 0, 0);
            func_101AB0(1, W(0x2E0), 0, 0);
            *(s32 *)(D_3876A4 + 0x468) = W(0x4CA8);
            *(s32 *)(D_3876A4 + 0x470) = W(0x8CA8);
            *(s32 *)(D_3876A4 + 0x46C) = W(0x4CAC);
            *(s32 *)(D_3876A4 + 0x474) = W(0x8CAC);
        } else if (mode == 0) {
            func_101AB0(0, W(0x2DC), 0, 0);
            func_101AB0(1, W(0x2E0), 1, 0);
        } else if (mode == 2) {
            func_101AB0(0, W(0x2DC), 1, 0);
            func_101AB0(1, W(0x2E0), 1, 0);
        }

        for (i = 0; i < 2; i++) {
            u8 *base = func_00101A88(i);
            if (W(0x2DC + i * 4) > 0) {
                k = 0;
                do {
                    idx = i * 5 + k;
                    if (W(0x30C + idx * 4) == 1) {
                        if (*(s32 *)(D_3876A4 + 0x4C8) != 0 && *(s32 *)(D_3876A4 + 0x4CC) != 0) {
                            s2 = *(s32 *)(D_3876A4 + 0x4C8 + i * 4);
                            t = W(0x244 + idx * 4) + W(0x26C + idx * 4) * 7;
                            s3 = func_0024B010(*(u8 **)(G + 0x37DC), *(u8 **)(G + 0x37E0), (u8 *)(s2 + t * 34 + 0x1408),
                                               (u8 *)o80, 0x14);
                            t = W(0x244 + idx * 4) + W(0x26C + idx * 4) * 7;
                            s1 = *(s16 *)(s2 + t * 34 + 0x1426);
                        } else {
                            t = W(0x244 + idx * 4) + W(0x26C + idx * 4) * 7;
                            s3 = func_0024B010(*(u8 **)(G + 0x37DC), *(u8 **)(G + 0x37E0),
                                               D_387F2C + t * 34 + 0x1408, (u8 *)o80, 0x14);
                            t = W(0x244 + idx * 4) + W(0x26C + idx * 4) * 7;
                            s1 = *(s16 *)(D_387F2C + t * 34 + 0x1426);
                        }
                        t = func_0024B7F0(o80[0]);
                        s2 = *(s32 *)(p74 + (W(0x2E4 + idx * 4) << 4)) + t;
                    } else {
                        s3 = 0;
                        s1 = 0;
                        for (j = 7; j >= 0; j--) o80[j] = 1;
                        s2 = *(s32 *)(p74 + (W(0x2E4 + idx * 4) << 4));
                    }
                    func_00101AF8(base + 8 + k * 0x58, tmp[idx], 0, *(s32 *)(D_387F2C + 0x810), s1,
                                  *(s32 *)(D_387F2C + i * 4 + 0x814) ^ 1, o80[0], o80[1], o80[2], o80[3], o80[4], o80[5],
                                  o80[6], o80[7], s3, s2, s2, *(s32 *)(p74 + (W(0x2E4 + idx * 4) << 4) + 4));
                    k++;
                } while (k < W(0x2DC + i * 4));
            }
        }
    }

    if (W(0x37C8) == 1) {
        __builtin_memcpy(D_387F2C, G + 0x3C14, 0x4000);
        __builtin_memcpy(*(u8 **)(D_3876A4 + 0x4D0), G + 0x901C, 0xB28);
        __builtin_memcpy(*(u8 **)(D_3876A4 + 0x4D4), G + 0x9B44, 0x90C);
        *(s32 *)(D_3876A4 + 0x4C8) = 0;
        *(s32 *)(D_3876A4 + 0x4CC) = 0;
    }
    func_0040C480(0);
    func_28B218();
    return v68;
}
