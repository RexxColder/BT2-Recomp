#include "common.h"

extern u8 *D_00428F4C __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));

extern s32 func_0026EB60();
extern s32 func_0026EB78();
extern s32 func_0026EAE0();
extern void func_003EE8D8(void);
extern void func_00243A80(s32 a0, s32 a1, s32 a2);
extern void func_0024C120(void);
extern void func_0024C0F0(void);
extern void func_002493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

#define G (D_00428F4C)
#define W(off) (*(s32 *)(G + (off)))
#define LIST(off) (*(s32 *)((u8 *)(8 * W(0x184) + W(0x1AC)) + (off)))

/* 0x003EFE18: menu input handler; G = D_00428F4C, state W(0x180) (0 main, 1 sub-menu). pad words D_003B0B00+0x144 / +0x134. */
void func_003EFE18(s32 *arg0) {
    s32 pad144, pad134, v, a, base, idx;

    if (func_0026EB60(G + 0xA0) == 0) {
        return;
    }
    if (W(0x180) == 0) {
        pad144 = *(s32 *)(D_003B0B00 + 0x144);
        if (pad144 & 0x10) {
            W(0x1A8) = 0;
            W(0x174) = W(0x174) & ~0x10;
            W(0x178) = W(0x178) - 1;
            if (W(0x178) < 0) {
                W(0x178) = 1;
            }
            func_003EE8D8();
            func_00297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if (pad144 & 0x40) {
            W(0x1A8) = 0;
            W(0x174) = W(0x174) & ~0x10;
            W(0x178) = W(0x178) + 1;
            if (!(W(0x178) < 2)) {
                W(0x178) = 0;
            }
            func_003EE8D8();
            func_00297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        pad134 = *(s32 *)(D_003B0B00 + 0x134);
        if (pad134 & 0x8000) {
            W(0x1A8) = 0;
            W(0x174) = W(0x174) & ~0x10;
            v = (W(0x174) & 4) ? 0x29 : 0x15;
            W(0x198) = v;
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            return;
        }
        if ((pad134 & 0x2000) && *(s16 *)(D_00387F2C + 0x27FE) > 0) {
            W(0x1A8) = 0;
            W(0x174) = W(0x174) & ~0x10;
            if (W(0x174) & 4) {
                func_0026EB78(G + 0x50, "fr_chara_in");
                a = 0xB5;
                v = W(0x174) ^ 4;
            } else {
                func_0026EB78(G + 0x50, "fr_chara_out");
                a = 0xA1;
                v = W(0x174) | 4;
            }
            W(0x174) = v;
            W(0x198) = a;
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            return;
        }
        pad134 = *(s32 *)(D_003B0B00 + 0x134);
        if (pad134 & 0x4000) {
            W(0x1A8) = 0;
            W(0x174) = W(0x174) & ~0x10;
            if (W(0x178) == 0) {
                func_0026EB78(G + 0xA0, "fr_menu_change");
                func_0026EAE0(G + 0x78, 0x3C);
                func_0026EB78(G + 0x78, "fr_menu_change");
                func_0024C120();
                if (!(W(0x174) & 4)) {
                    func_0026EB78(G + 0x50, "fr_buruma_out");
                }
                W(0x180) = 1;
            } else if (W(0x178) == 1) {
                W(0x174) = W(0x174) | 1;
                W(0x174) = W(0x174) | 2;
                W(0x19C) = 0xF;
                *(s32 *)(D_003876A4 + 0x1C) = 0x3F;
            }
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            return;
        }
        if (pad134 & 0x1000) {
            W(0x1A8) = 0;
            W(0x174) = W(0x174) & ~0x10;
            if (W(0x174) & 4) {
                func_00243A80(0, 0, 0);
                *arg0 = 0;
            } else {
                W(0x198) = 0x3D;
            }
            func_00297FE0(0, 2, 0x40, 0x40, 1);
            return;
        }
    } else if (W(0x180) == 1) {
        pad144 = *(s32 *)(D_003B0B00 + 0x144);
        if (pad144 & 0x80) {
            W(0x1A8) = 0;
            W(0x174) = W(0x174) & ~0x10;
            W(0x194) = 1;
            return;
        }
        if (pad144 & 0x20) {
            W(0x1A8) = 0;
            W(0x174) = W(0x174) & ~0x10;
            W(0x194) = 0x15;
            return;
        }
        if (pad144 & 0x10) {
            W(0x18C) = W(0x18C) - 1;
            if (W(0x18C) < 0) {
                W(0x18C) = 0;
                W(0x188) = W(0x188) - 1;
                if (W(0x188) < 0) {
                    W(0x188) = 0;
                    return;
                }
            }
            func_00297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        if (pad144 & 0x40) {
            W(0x18C) = W(0x18C) + 1;
            v = LIST(4);
            a = W(0x18C);
            if (!(a < v)) {
                W(0x18C) = v - 1;
                return;
            }
            if (!(a < 3)) {
                W(0x18C) = 2;
                W(0x188) = W(0x188) + 1;
                v = LIST(4);
                if (v < W(0x188) + 3) {
                    W(0x188) = v - 3;
                    return;
                }
            }
            func_00297FE0(0, 0, 0x40, 0x40, 1);
            return;
        }
        pad134 = *(s32 *)(D_003B0B00 + 0x134);
        if ((pad134 & 0x4000) && func_0026EB60(G + 0x78) != 0) {
            *(s32 *)(D_003876A4 + 0x484) = W(0x188) + W(0x18C);
            *(s32 *)(D_003876A4 + 0x488) = 0;
            if (LIST(0) == 1) {
                W(0x1A4) = 0;
                base = W(0x1C4);
                idx = *(s32 *)((u8 *)base + (W(0x188) + W(0x18C)) * 4);
                W(0x24) = *(s32 *)((u8 *)base + idx * 4 + 4);
                W(0x1F0) = 0;
                W(0x194) = 0x29;
            } else {
                W(0x198) = 0x51;
            }
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            return;
        }
        pad134 = *(s32 *)(D_003B0B00 + 0x134);
        if (pad134 & 0x1000) {
            func_0026EB78(G + 0xA0, "fr_menu_change_return");
            func_0026EB78(G + 0x78, "fr_menu_change_return");
            func_0024C0F0();
            if (W(0x174) & 4) {
                W(0x180) = 0;
            } else {
                func_0026EB78(G + 0x50, "fr_buruma_in");
                W(0x180) = 0;
            }
            func_00297FE0(0, 2, 0x40, 0x40, 1);
            return;
        }
    } else {
        return;
    }
    if (W(0x174) & 0x10) {
        return;
    }
    W(0x1A8) = W(0x1A8) + 1;
    if (W(0x1A8) != 600) {
        return;
    }
    if (W(0x174) & 4) {
        W(0x17C) = 0x31;
        W(0x190) = 3;
    } else {
        W(0x17C) = 0x30;
        W(0x190) = 0;
    }
    func_002493C0(W(0xC), 0x3711, 0x3B2A, 0, W(0x17C));
    W(0x1A8) = 0;
    W(0x174) = W(0x174) | 0x10;
}
