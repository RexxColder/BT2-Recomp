#include "common.h"

extern u8 *D_0042BB70 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 D_0042D808[] __attribute__((section(".data")));
extern u8 D_0042D818[] __attribute__((section(".data")));
extern u8 D_0042D828[] __attribute__((section(".data")));
extern u8 D_0042D838[] __attribute__((section(".data")));
extern u8 D_0042D848[] __attribute__((section(".data")));
extern u8 D_0042D860[] __attribute__((section(".data")));
extern u8 D_0042D870[] __attribute__((section(".data")));
extern u8 D_0042D880[] __attribute__((section(".data")));
extern u8 D_0042D890[] __attribute__((section(".data")));
extern u8 D_0042D8A0[] __attribute__((section(".data")));

s32 func_0026EB60(u8 *a0);
void func_0026EB78(u8 *a0, u8 *a1);
void func_0029C7E0(s32 a0);
void func_0029C550(s32 a0);
void func_0029C820(s32 a0);
void func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_00243A80(s32 a0, s32 a1, s32 a2);
void func_004047C8(s32 a0);

#define G (D_0042BB70)
#define F(off) (*(s32 *)(G + (off)))
#define PAD34 (*(s32 *)(D_003B0B00 + 0x134))
#define PAD44 (*(s32 *)(D_003B0B00 + 0x144))

#define OUT_NAME() do { switch (F(0x110)) { \
    case 0: func_0026EB78(G + 0x38, D_0042D808); break; \
    case 1: func_0026EB78(G + 0x38, D_0042D818); break; \
    case 2: func_0026EB78(G + 0x38, D_0042D838); break; \
    case 3: func_0026EB78(G + 0x38, D_0042D828); break; \
    case 4: func_0026EB78(G + 0x38, D_0042D848); break; \
    default: break; \
    } } while (0)

/* Menu state step, a0 = u32 * (cleared on cancel). G = D_0042BB70; F(0x10C) flags (0x4 open, 0x8, 0x10, 0x20), 0x110
 * current row (0..5), 0x118/0x11C/0x120 sub selection, saved at 0x168 + 4 * 0x118. */
void func_004049F8(s32 *arg0) {
    s32 v;
    s32 a;
    s32 r;

    if (!func_0026EB60(G + 0x38)) {
        return;
    }
    if (F(0x10C) & 0x10) {
        if (F(0x364) != 0) {
            return;
        }
        if (F(0x36C) <= 0) {
            F(0x10C) = F(0x10C) ^ 0x10;
            return;
        }
        F(0x168) = 4;
        F(0x16C) = 2;
        F(0x170) = 0;
        F(0x174) = 0;
        F(0x178) = 1;
        F(0x17C) = 1;
        __builtin_memcpy(D_00387F2C + 0x808, G + 0x164, 0x200);
        *(s32 *)(D_003876A4 + 0x18) = *(s32 *)(D_003876A4 + 0x18) | 1;
        F(0x10C) = F(0x10C) ^ 0x10;
        return;
    }

    if (!(F(0x10C) & 4)) {
        if (PAD44 & 0x10) {
            F(0x110) = F(0x110) - 1;
            if (F(0x110) < 0) {
                F(0x110) = 5;
            }
        } else {
            if (!(PAD44 & 0x40)) {
                if (PAD34 & 0x4000) {
                    switch (F(0x110)) {
                    case 0: func_0026EB78(G + 0x38, D_0042D860); break;
                    case 1:
                        func_0026EB78(G + 0x38, D_0042D870);
                        F(0x10C) = F(0x10C) | 0x20;
                        break;
                    case 2: func_0026EB78(G + 0x38, D_0042D890); break;
                    case 3:
                        func_0026EB78(G + 0x38, D_0042D880);
                        F(0x10C) = F(0x10C) | 0x20;
                        break;
                    case 4: func_0026EB78(G + 0x38, D_0042D8A0); break;
                    default: break;
                    }
                    if (F(0x110) == 5) {
                        F(0x10C) = F(0x10C) | 0x10;
                        F(0x364) = 1;
                        func_0029C7E0(0);
                        func_0029C550(0);
                        func_0029C820(1);
                        F(0x36C) = 0;
                    } else {
                        v = F(0x10C);
                        if (F(0x110) == 4) {
                            v = v | 8;
                            F(0x10C) = v;
                        }
                        F(0x10C) = v | 4;
                    }
                    func_00297FE0(0, 1, 64, 64, 1);
                    return;
                }
                if (PAD34 & 0x1000) {
                    func_00243A80(0, 0, 0);
                    *arg0 = 0;
                    func_00297FE0(0, 2, 64, 64, 1);
                }
                return;
            }
            F(0x110) = F(0x110) + 1;
            if (F(0x110) >= 6) {
                F(0x110) = 0;
            }
        }
        func_004047C8(0);
        func_00297FE0(0, 0, 64, 64, 1);
        return;
    }

    /* open: move the sub selection */
    if (!(F(0x10C) & 0x20)) {
        if (PAD44 & 0x80) {
            goto dec;
        }
    } else {
        if (PAD44 & 0x10) {
            goto dec;
        }
    }
    if (F(0x10C) & 0x20) {
        if (PAD44 & 0x40) {
            goto inc;
        }
    } else {
        if (PAD44 & 0x20) {
            goto inc;
        }
    }
    goto buttons;
dec:
    F(0x11C) = F(0x11C) - 1;
    if (F(0x11C) < 0) {
        F(0x11C) = F(0x120) - 1;
    }
    func_00297FE0(0, 0, 64, 64, 1);
    return;
inc:
    F(0x11C) = F(0x11C) + 1;
    if (!(F(0x11C) < F(0x120))) {
        F(0x11C) = 0;
    }
    func_00297FE0(0, 0, 64, 64, 1);
    return;

buttons:
    if (PAD34 & 0x4000) {
        F(0x168 + F(0x118) * 4) = F(0x11C);
        __builtin_memcpy(D_00387F2C + 0x808, G + 0x164, 0x200);
        OUT_NAME();
        v = F(0x10C);
        if (v & 8) {
            F(0x10C) = F(0x10C) ^ 8;
            v = F(0x10C);
        }
        if (v & 0x20) {
            F(0x10C) = v ^ 0x20;
        }
        F(0x10C) = F(0x10C) ^ 4;
        func_00297FE0(0, 1, 64, 64, 1);
        return;
    }
    if (PAD34 & 0x1000) {
        OUT_NAME();
        F(0x11C) = F(0x168 + F(0x118) * 4);
        v = F(0x10C);
        if (v & 8) {
            F(0x10C) = F(0x10C) ^ 8;
            v = F(0x10C);
        }
        if (v & 0x20) {
            F(0x10C) = v ^ 0x20;
        }
        F(0x10C) = F(0x10C) ^ 4;
        func_00297FE0(0, 2, 64, 64, 1);
        return;
    }
    if (F(0x10C) & 8) {
        if (PAD44 & 0x50) {
            F(0x168 + F(0x118) * 4) = F(0x11C);
            if (F(0x118) == 2) {
                a = 3;
            } else {
                a = F(0x118) - 1;
            }
            F(0x118) = a;
            F(0x11C) = F(0x168 + F(0x118) * 4);
            func_00297FE0(0, 0, 64, 64, 1);
        }
    }
}
