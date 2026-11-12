#include "common.h"

extern s32 func_0026EB60();
extern s32 func_0026EB78();
extern s32 func_002A0EA8();
extern s32 EftShotFx_Update_2494A0();
extern void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_00101700(s32 arg0);
extern void func_003DD0C0(void);

extern u8 *D_0042732C __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 D_004274B0[] __attribute__((section(".data")));
extern u8 D_004274C0[] __attribute__((section(".data")));
extern u8 D_004274D0[] __attribute__((section(".data")));
extern u8 D_004274E0[] __attribute__((section(".data")));

#define G (D_0042732C)
#define W(p, o) (*(s32 *)((p) + (o)))
#define N(p, o) (*(u8 **)((p) + (o)))
#define SND(a, b) func_00297FE0((a), (b), 0x40, 0x40, 1)

/* Memory-card list input handler (modes in G+0x744: 0 list, 1 detail, 2 other). Return value not modelled. */
void func_003DDE30(s32 *arg0) {
    u8 *s0, *a2, *v;
    s32 n, a0, a1, a3, A, B, C, i, r, vv;
    u8 *P = D_003B0B00;

    s0 = N(G, 0x114);
    n = W(G, 0x110);
    if (n > 0) {
        for (i = n; i != 0; i--) {
            s0 = N(s0, 8);
        }
    }
    if (func_0026EB60(G + 0x2C) == 0) {
        return;
    }
    a3 = W(G, 0x108);
    if (a3 & 0x40) {
        return;
    }
    if (W(G, 0x744) == 0) {
        A = W(P, 0x144);
        if (A & 0x50) {
            if ((A & 0x10) != 0 && W(G, 0x770) <= 0) {
                W(G, 0x110) = W(G, 0x110) - 1;
                if (W(G, 0x110) >= 0) {
                    SND(0, 0);
                    goto set770;
                }
                W(G, 0x110) = 0;
                a2 = N(G, 0x114);
                v = N(a2, 0);
                if (v == 0 || a2 == v) {
                    goto set770;
                }
                N(G, 0x114) = v;
                SND(0, 0);
                goto set770;
            }
            if ((W(P, 0x144) & 0x40) == 0) {
                return;
            }
            if (W(G, 0x770) > 0) {
                return;
            }
            n = W(G, 0x110) + 1;
            a2 = N(G, 0x114);
            W(G, 0x110) = n;
            if (n < 4) {
                SND(0, 0);
                goto set770;
            }
            W(G, 0x110) = 3;
            a0 = 1;
            v = N(a2, 8);
            for (a1 = 3; a1 >= 0; a1--) {
                if (v != 0) {
                    a2 = v;
                } else {
                    a0 = 0;
                }
                v = N(a2, 8);
            }
            if (a0 == 0) {
                goto set770;
            }
            v = N(G, 0x114);
            a2 = N(v, 8);
            if (v == a2) {
                goto set770;
            }
            N(G, 0x114) = a2;
            SND(0, 0);
        set770:
            W(G, 0x770) = 6;
            return;
        }
        if ((A & 0xCA0) != 0) {
            if ((A & 0x480) != 0) {
                if (W(N(G, 0x114), 0) == 0) {
                    if (W(G, 0x110) <= 0) {
                        return;
                    }
                    W(G, 0x110) = 0;
                    SND(0, 0);
                    return;
                }
                for (a1 = 3; a1 >= 0; a1--) {
                    v = N(N(G, 0x114), 0);
                    if (v != 0) {
                        N(G, 0x114) = v;
                    }
                }
                SND(0, 0);
                return;
            }
            if ((A & 0x820) == 0) {
                return;
            }
            a2 = N(G, 0x114);
            a0 = 1;
            v = N(a2, 8);
            for (i = 3; i >= 0; i--) {
                if (v != 0) {
                    a2 = v;
                } else {
                    a0 = 0;
                }
                v = N(a2, 8);
            }
            if (a0 != 0) {
                for (a1 = 3; a1 >= 0; a1--) {
                    a0 = 1;
                    a2 = N(G, 0x114);
                    v = N(a2, 8);
                    for (i = 3; i >= 0; i--) {
                        if (v != 0) {
                            a2 = v;
                        } else {
                            a0 = 0;
                        }
                        v = N(a2, 8);
                    }
                    if (a0 != 0) {
                        N(G, 0x114) = N(N(G, 0x114), 8);
                    }
                }
                SND(0, 0);
                return;
            }
            if (!(W(G, 0x110) < 3)) {
                return;
            }
            W(G, 0x110) = 3;
            SND(0, 0);
            return;
        }
        B = W(P, 0x134);
        if (B & 0x100) {
            v = N(G, 0x114);
            if (W(v, 0) == 0) {
                if (W(G, 0x110) == 0) {
                    return;
                }
            } else {
                do {
                    N(G, 0x114) = N(N(G, 0x114), 0);
                } while (N(N(G, 0x114), 0) != 0);
            }
            W(G, 0x110) = 0;
            SND(0, 0);
            return;
        }
        if (B & 0x200) {
            a2 = N(G, 0x114);
            a1 = 0;
            a3 = (s32)a2;
            if (a2 == 0) {
                r = 1;
            } else {
                a2 = N(a2, 8);
                for (;;) {
                    a1++;
                    r = a1 < 4;
                    if (a2 == 0 || a1 >= 4) {
                        break;
                    }
                    a2 = N(a2, 8);
                }
            }
            if (r) {
                return;
            }
            while (N(N(G, 0x114), 8) != 0) {
                N(G, 0x114) = N(N(G, 0x114), 8);
            }
            for (a1 = 2; a1 >= 0; a1--) {
                v = N(N(G, 0x114), 0);
                if (v != 0) {
                    N(G, 0x114) = v;
                }
            }
            W(G, 0x110) = 3;
            if ((u8 *)a3 == N(G, 0x114)) {
                return;
            }
            SND(0, 0);
            return;
        }
        if (B & 0x4000) {
            a0 = W(s0, 4);
            if (a0 < 0x62) {
                vv = a0 * 4 + 0x25E8;
            } else {
                vv = a0 * 4 + 0x25E4;
            }
            if (*(s16 *)(D_00387F2C + vv + 2) <= 0) {
                SND(0, 7);
                return;
            }
            W(G, 0x744) = 1;
            SND(0, 1);
            func_0026EB78(G + 0x2C, D_004274B0);
            func_003DD0C0();
            v = N(G, 0x114);
            n = W(G, 0x110);
            if (n > 0) {
                for (; n != 0; n--) {
                    v = N(v, 8);
                }
            }
            {
                u8 *b = N(G, 0x28);
                u32 t = *(u32 *)(b + W(v, 4) * 4 + 4);
                W(G, 0x760) = func_002A0EA8(b + ((t >> 2) << 2));
            }
            W(G, 0x754) = 0;
            W(G, 0x758) = 0;
            EftShotFx_Update_2494A0();
            return;
        }
        if ((B & 0x1000) == 0) {
            return;
        }
        W(G, 0x744) = 2;
        W(G, 0x108) = 2;
        *arg0 = 0;
        SND(0, 2);
        return;
    }

    if (W(G, 0x744) != 1) {
        return;
    }

    A = W(P, 0x144);
    if ((A & 0xC00) == 0) {
        C = W(P, 0x12C);
        if ((C & 0x50) == 0) {
            B = W(P, 0x134);
            if (B & 0x8000) {
                W(G, 0x764) = 1;
                return;
            }
            if (B & 0x2000) {
                W(G, 0x108) = a3 | 0x40;
                SND(0, 1);
                return;
            }
            if ((B & 0x1000) == 0) {
                return;
            }
            W(G, 0x744) = 0;
            SND(0, 2);
            func_0026EB78(G + 0x2C, D_004274E0);
            func_00101700(0);
            return;
        }
        if (W(G, 0x760) < 8) {
            return;
        }
        {
            s32 v1 = W(G, 0x754);
            f32 f3 = (f32)W(G, 0x75C);
            f32 f2 = (f32)W(G, 0x758);
            f32 f1 = (f32)v1;
            f32 f0 = (f1 - 0.5f) * f3;
            if (!(f0 <= f2)) {
                return;
            }
            f0 = (f1 + 0.5f) * f3;
            if (!(f2 <= f0)) {
                return;
            }
            if (C & 0x10) {
                W(G, 0x754) = v1 - 1;
                if (W(G, 0x754) < 0) {
                    W(G, 0x754) = 0;
                    return;
                }
                SND(0, 0);
                return;
            }
            if ((C & 0x40) == 0) {
                return;
            }
            W(G, 0x754) = v1 + 1;
            vv = W(G, 0x760) - 7;
            if (vv < W(G, 0x754)) {
                W(G, 0x754) = vv;
                return;
            }
            SND(0, 0);
            return;
        }
    }

    W(G, 0x748) = W(s0, 4);
    A = W(P, 0x144);
    if (A & 0x400) {
        W(G, 0x110) = W(G, 0x110) - 1;
        if (W(G, 0x110) < 0) {
            W(G, 0x110) = 0;
            v = N(N(G, 0x114), 0);
            if (v == 0) {
                return;
            }
            N(G, 0x114) = v;
        }
        func_0026EB78(G + 0x2C, D_004274C0);
        W(G, 0x108) &= -9;
        func_003DD0C0();
        SND(2, 0);
        return;
    }
    if ((A & 0x800) == 0) {
        return;
    }
    n = W(G, 0x110) + 1;
    a2 = N(G, 0x114);
    W(G, 0x110) = n;
    if (n >= 4) {
        W(G, 0x110) = 3;
        a0 = 1;
        v = N(a2, 8);
        for (a1 = 3; a1 >= 0; a1--) {
            if (v != 0) {
                a2 = v;
            } else {
                a0 = 0;
            }
            v = N(a2, 8);
        }
        if (a0 == 0) {
            return;
        }
        N(G, 0x114) = N(N(G, 0x114), 8);
    }
    func_0026EB78(G + 0x2C, D_004274D0);
    W(G, 0x108) &= -9;
    func_003DD0C0();
    SND(2, 0);
}
