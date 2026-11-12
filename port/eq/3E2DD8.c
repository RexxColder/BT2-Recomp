#include "common.h"

extern u8 *D_004279C8 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));

void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_29C7E0(s32 arg0);
void func_29C550(s32 arg0);
void func_29C820(s32 arg0);
void func_003E1AE0(void);
void func_2493C0(s32, s32, s32, s32, s32);
void EftShotFx_Update_2494A0(void *);

#define G (D_004279C8)
#define W(off) (*(s32 *)(G + (off)))
#define IN144 (*(s32 *)(D_003B0B00 + 0x144))
#define IN134 (*(s32 *)(D_003B0B00 + 0x134))
#define IN12C (*(s32 *)(D_003B0B00 + 0x12C))
#define SEL(i) (*(s32 *)(G + 0x1B0 + (W(0xC4) * 8 + (i)) * 4))
#define FLAGS() (*(s32 *)(D_003876A4 + 0x18) |= 1)

/* 0x003E2DD8: menu (controller config) input step. G = *D_004279C8 */
void func_003E2DD8(s32 *a0) {
    s32 i, j, v, m, t, sel;

    if (W(0xC0) & 2) {
        if (W(0x378) != 0) return;
        if (W(0x380) <= 0) {
            W(0xC0) = W(0xC0) ^ 2;
            return;
        }
        v = (W(0xC4) != 0) ? -5 : -3;
        W(0x16C) = W(0x16C) & v;
        W(0x1F0 + W(0xC4) * 4) = 0;
        for (i = 0; i < 8; i++) {
            m = *(s32 *)(G + 0xCC + i * 4);
            W(0x1B0 + (W(0xC4) * 8 + i) * 4) = m;
        }
        FLAGS();
        W(0xC0) = W(0xC0) ^ 2;
        return;
    }

    if ((W(0xC0) & 1) == 0) {
        if (IN144 & 0x20) {
            W(0xC4) = W(0xC4) + 1;
            if (!(W(0xC4) < 2)) W(0xC4) = 0;
        } else if (IN144 & 0x80) {
            W(0xC4) = W(0xC4) - 1;
            if (W(0xC4) < 0) W(0xC4) = 1;
        } else if (IN134 & 0x4000) {
            W(0xC0) = W(0xC0) | 1;
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            W(0xC8) = 0;
            func_003E1AE0();
            return;
        } else if (IN134 & 0x1000) {
            for (i = 0; i < 2; i++) {
                if (W(0x1F0 + i * 4) == 5) {
                    __builtin_memcpy(G + 0x170 + i * 32, G + 0x1B0 + i * 32, 32);
                } else {
                    for (j = 0; j < 8; j++) {
                        W(0x170 + i * 32 + j * 4) = *(s32 *)(G + 0xCC + (W(0x1F0 + i * 4) * 8 + j) * 4);
                    }
                }
            }
            __builtin_memcpy(D_00387F2C + 0x1008, G + 0x16C, 0xAC);
            *a0 = 0;
            func_243A80(0, 0, 0);
            func_00297FE0(0, 2, 0x40, 0x40, 1);
            return;
        } else {
            return;
        }
        func_00297FE0(0, 0, 0x40, 0x40, 1);
        func_003E1AE0();
        return;
    }

    if (W(0xC8) == 0) {
        if (W(0x1F0 + W(0xC4) * 4) == 5) {
            sel = W(0x36C);
            if (sel == -1) {
                if (IN134 & 0x100) W(0x36C) = 5;
                else if (IN134 & 0x400) W(0x36C) = 4;
                else if (IN134 & 0x200) W(0x36C) = 7;
                else if (IN134 & 0x800) W(0x36C) = 6;
                else if (IN134 & 0x1000) W(0x36C) = 3;
                else if (IN134 & 0x8000) W(0x36C) = 2;
                else if (IN134 & 0x2000) W(0x36C) = 0;
                else if (IN134 & 0x4000) W(0x36C) = 1;
                else W(0x36C) = -1;
                if (W(0x36C) != -1) {
                    W(0x370) = SEL(W(0x36C));
                    func_00297FE0(0, 1, 0x40, 0x40, 1);
                    return;
                }
                goto L83;
            }
            v = 0;
            if ((u32)sel < 8) {
                switch (sel) {
                case 0: v = IN12C & 0x2000; break;
                case 1: v = IN12C & 0x4000; break;
                case 2: v = IN12C & 0x8000; break;
                case 3: v = IN12C & 0x1000; break;
                case 4: v = IN12C & 0x400; break;
                case 5: v = IN12C & 0x100; break;
                case 6: v = IN12C & 0x800; break;
                case 7: v = IN12C & 0x200; break;
                }
            }
            if (v != 0) {
                sel = W(0x36C);
                if (sel < 0) return;
                if (IN144 & 0x20) {
                    t = SEL(sel) + 1;
                    SEL(sel) = t;
                    if (!(t < 8)) SEL(W(0x36C)) = 0;
                } else if (IN144 & 0x80) {
                    t = SEL(sel) - 1;
                    SEL(sel) = t;
                    if (t < 0) SEL(W(0x36C)) = 7;
                } else {
                    return;
                }
                FLAGS();
                func_00297FE0(0, 0, 0x40, 0x40, 1);
                return;
            }
            sel = W(0x36C);
            for (i = 0; i < 8; i++) {
                if (i == sel) continue;
                if (SEL(i) == SEL(sel)) {
                    SEL(i) = W(0x370);
                    break;
                }
            }
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            W(0x36C) = -1;
            return;
        }
L83:
        if (IN144 & 0x20) {
            t = W(0x1F0 + W(0xC4) * 4) + 1;
            W(0x1F0 + W(0xC4) * 4) = t;
            if (!(W(0x1F0 + W(0xC4) * 4) < 6)) W(0x1F0 + W(0xC4) * 4) = 0;
        } else if (IN144 & 0x80) {
            t = W(0x1F0 + W(0xC4) * 4) - 1;
            W(0x1F0 + W(0xC4) * 4) = t;
            if (W(0x1F0 + W(0xC4) * 4) < 0) W(0x1F0 + W(0xC4) * 4) = 5;
        } else {
            goto L112;
        }
        func_00297FE0(0, 0, 0x40, 0x40, 1);
        FLAGS();
        W(0xBC) = W(0x1F0 + W(0xC4) * 4) + 13;
        if (W(0xBC) == 0x12) EftShotFx_Update_2494A0(G);
        else func_2493C0(W(0xC), 0x36EF, 0x3B08, 0, W(0xBC));
        goto L112;
    }

    if (W(0xC8) == 1) {
        if ((IN144 & 0xA0) == 0) goto L113;
        if (W(0xC4) == 0) {
            W(0x16C) = W(0x16C) ^ 2;
            FLAGS();
            W(0xBC) = (W(0x16C) & 2) ? 0x14 : 0x13;
            if (W(0xBC) == 0x12) EftShotFx_Update_2494A0(G);
            else func_2493C0(W(0xC), 0x36EF, 0x3B08, 0, W(0xBC));
        } else {
            W(0x16C) = W(0x16C) ^ 4;
            FLAGS();
            W(0xBC) = (W(0x16C) & 4) ? 0x14 : 0x13;
            if (W(0xBC) == 0x12) EftShotFx_Update_2494A0(G);
            else func_2493C0(W(0xC), 0x36EF, 0x3B08, 0, W(0xBC));
        }
        *(s32 *)(D_00387F2C + 0x1008) = W(0x16C);
        func_00297FE0(0, 0, 0x40, 0x40, 1);
        goto L112;
    }

    if (W(0xC8) == 2) {
        if (IN134 & 0x4000) {
            W(0xC0) = W(0xC0) | 2;
            W(0x378) = 1;
            func_29C7E0(0);
            func_29C550(0);
            func_29C820(1);
            W(0x380) = 0;
        }
    }
L112:
L113:
    if (IN144 & 0x10) {
        W(0xC8) = W(0xC8) - 1;
        if (W(0xC8) < 0) W(0xC8) = 2;
    } else if (IN144 & 0x40) {
        W(0xC8) = W(0xC8) + 1;
        if (!(W(0xC8) < 3)) W(0xC8) = 0;
    } else {
        if (IN134 & 0x1000) {
            W(0xC0) = W(0xC0) & -2;
            func_00297FE0(0, 2, 0x40, 0x40, 1);
        }
        return;
    }
    func_00297FE0(0, 0, 0x40, 0x40, 1);
    func_003E1AE0();
}
