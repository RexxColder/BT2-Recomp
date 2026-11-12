#include "common.h"

extern s32 func_00277E70();
extern s32 func_0026EBC0();
extern s32 func_00249FB8();
extern s32 func_002495A8();
extern s32 func_00249778();
extern s32 func_00325830();
extern s32 func_0026EC48();
extern s32 func_0026EFC8();
extern s32 func_0026EEC8();
extern s32 func_0026EA58();
extern s32 func_002A0EA8();
extern s32 func_00249BB8();
extern s32 func_00249DB8();
extern s32 func_0024A350();
extern s32 func_0024A598();
extern f32 func_0026F148(s32 arg0, u8 *arg1);
extern void func_0026EEF8(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, f32 farg0);
extern s32 func_0026EF38(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);
extern void func_003DC7A8(s32 a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, s32 t2, s32 t3, s32 s8);

extern u8 *D_0042732C __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 D_004273A8[] __attribute__((section(".data")));
extern u8 D_004273B8[] __attribute__((section(".data")));
extern u8 D_004273C8[] __attribute__((section(".data")));
extern u8 D_004273D8[] __attribute__((section(".data")));
extern u8 D_004273E8[] __attribute__((section(".data")));
extern u8 D_004273F8[] __attribute__((section(".data")));
extern u8 D_00427408[] __attribute__((section(".data")));
extern u8 D_00427418[] __attribute__((section(".data")));
extern u8 D_00427428[] __attribute__((section(".data")));
extern u8 D_00427438[] __attribute__((section(".data")));
extern u8 D_00427450[] __attribute__((section(".data")));
extern u8 D_00427468[] __attribute__((section(".data")));
extern u8 D_00427478[] __attribute__((section(".data")));
extern u8 D_00427488[] __attribute__((section(".data")));
extern u8 D_00427498[] __attribute__((section(".data")));

#define G (D_0042732C)
#define W(p, o) (*(s32 *)((p) + (o)))
#define N(p, o) (*(u8 **)((p) + (o)))

void func_003DD160(void) {
    u8 sp[0x50];
    s32 *r = (s32 *)(sp + 0x10);
    u8 *obj = sp;
    u8 *s7, *s3, *s0, *g, *a0;
    s32 s2, s1, i, n, v, a3, a2;
    f32 f1, f2, f20;

    s7 = N(G, 0x114);
    n = W(G, 0x110);
    if (n > 0) {
        for (i = n; i != 0; i--) {
            s7 = N(s7, 8);
        }
    }
    s2 = (s32)(G + 0x2C);
    func_00277E70(N(G, 0x80), 0, 0x80);
    func_0026EBC0(s2, D_004273A8, obj);
    func_002495A8(s2, obj, (s32)(G + 0x73C), 1);
    func_0026EBC0(s2, D_004273B8, obj);
    func_00249778(s2, obj, (s32)(G + 0x740), 3);
    func_0026EBC0(s2, D_004273C8, obj);
    func_00249FB8(s2, obj, 0, 0, W(G, 0x10), W(G, 0x10C), 1);
    func_0026EBC0(s2, D_004273D8, obj);
    a3 = 0;
    for (s1 = 0; s1 < 4; s1++) {
        if (s1 == W(G, 0x110)) {
            func_0026EEC8(s2, obj, 0, a3);
            break;
        }
        a3 += 0x3A;
    }
    s3 = N(G, 0x114);
    func_0026EBC0(s2, D_004273E8, obj, a3);
    if (W(G, 0x754) > 0) {
        func_0026EFC8(s2, obj, 4);
    } else {
        func_0026EFC8(s2, obj, 8);
    }
    func_0026EBC0(s2, D_004273F8, obj);
    if (W(N(G, 0x114), 0) != 0) {
        func_0026EFC8(s2, obj, 4);
    } else {
        func_0026EFC8(s2, obj, 8);
    }
    r[2] = 0x40;
    r[3] = 0x20;
    r[0] = 0x20;
    r[1] = 0;
    for (s1 = 3; s1 >= 0; s1--) {
        if (s3 != 0) {
            s3 = N(s3, 8);
        }
    }
    func_0026EBC0(s2, D_00427408, obj);
    func_0026EC48(s2, obj, sp + 0x10);
    if (s3 != 0) {
        func_0026EFC8(s2, obj, 4);
    } else {
        func_0026EFC8(s2, obj, 8);
    }
    func_0026EBC0(s2, D_00427418, obj);
    func_0026EC48(s2, obj, sp + 0x10);
    if (W(G, 0x754) < W(G, 0x760) - 7) {
        func_0026EFC8(s2, obj, 4);
    } else {
        func_0026EFC8(s2, obj, 8);
    }
    r[0] = 0;
    r[3] = 0x40;
    r[1] = 0x20;
    r[2] = 0x20;
    s0 = N(G, 0x114);
    func_0026EBC0(s2, D_00427428, obj);
    r[1] = 0;
    if (W(G, 0x110) == 0) {
        r[1] = (W(s0, 0) == 0) ? 0x20 : 0;
    }
    n = W(G, 0x110);
    if (n > 0) {
        for (i = n; i != 0; i--) {
            if (s0 != 0) {
                s0 = N(s0, 8);
            }
        }
    }
    if (s0 != 0 && W(s0, 8) == 0) {
        r[1] = 0x40;
    }
    r[2] = 0x200;
    r[3] = r[1] + 0x20;
    r[0] = 0;
    func_0026EC48(s2, obj, sp + 0x10);

    s3 = N(G, 0x114);
    for (s1 = 0; ; ) {
        func_00325830(sp + 0x30, D_00427438, s1);
        func_0026EBC0(s2, sp + 0x30, obj);
        f1 = func_0026F148(s2, obj);
        if (f1 < 0.01f) {
            if (W(G, 0x744) == 1) {
                W(G, 0x108) |= 4;
                a0 = N(G, 0x114);
                n = W(G, 0x110);
                if (n > 0) {
                    for (; n != 0; n--) {
                        a0 = N(a0, 8);
                    }
                }
                {
                    u8 *a1 = N(G, 0x28);
                    u32 t = *(u32 *)(a1 + W(a0, 4) * 4 + 4);
                    W(G, 0x760) = func_002A0EA8(a1 + ((t >> 2) << 2));
                }
                W(G, 0x754) = 0;
                W(G, 0x758) = 0;
            } else {
                W(G, 0x108) &= ~4;
            }
            W(G, 0x108) |= 8;
        }
        if (W(G, 0x108) & 4) {
            s32 t0, t1;
            if (W(G, 0x108) & 8) {
                t0 = W(G, 0x20);
                t1 = W(s7, 4);
            } else {
                t1 = W(G, 0x748);
                t0 = W(G, 0x20);
            }
            func_00249BB8(s2, obj, 0, 0, t0, t1, 0);
        } else {
            func_0024A350(s2, obj, 8, 2, W(G, 0x20), W(s3, 4) + 1, 0, 0x100, 0x212FA1FF, -0x100);
        }
        func_00325830(sp + 0x30, D_00427450, s1);
        func_0026EBC0(s2, sp + 0x30, obj);
        if (W(G, 0x108) & 4) {
            s32 t0, t1;
            if (W(G, 0x108) & 8) {
                t0 = W(G, 0x24);
                t1 = W(s7, 4);
            } else {
                t1 = W(G, 0x748);
                t0 = W(G, 0x24);
            }
            func_00249DB8(s2, obj, 0, 0, t0, t1, 0);
        } else {
            func_0024A350(s2, obj, 8, 4, W(G, 0x24), W(s3, 4) + 1, 0, 0xF6, -1, 0x60FF);
        }
        if (W(G, 0x108) & 4) {
            break;
        }
        s1++;
        s3 = N(s3, 8);
        if (!(s1 < 4)) {
            break;
        }
    }

    func_0026EBC0(s2, D_00427468, obj);
    {
        s32 t1, t2;
        g = G;
        if (W(g, 0x108) & 8) {
            t1 = W(s7, 4);
        } else {
            t1 = W(g, 0x748);
        }
        t2 = t1 + 0x83;
        t1 = t1 + 0x10C;
        if ((W(D_00387F2C, 0x1008) & 1) == 0) {
            t1 = t2;
        }
        func_0024A598(s2, (s32 *)obj, 0, 8, N(g, 0x28), t1, 0);
    }
    func_0026EBC0(s2, D_00427478, obj);
    g = G;
    if (W(g, 0x108) & 8) {
        func_003DC7A8(s2, obj, 0, 5, N(g, 0x28), W(s7, 4) + 1, 0, W(g, 0x758), 7);
    } else {
        func_003DC7A8(s2, obj, 0, 5, N(g, 0x28), W(g, 0x748) + 1, 0, W(g, 0x758), 7);
    }
    g = G;
    if (W(g, 0x108) & 0x20) {
        *(f32 *)(g + 0x750) = *(f32 *)(g + 0x750) + 0.075f;
        if (1.0f <= *(f32 *)(G + 0x750)) {
            *(f32 *)(G + 0x750) = 1.0f;
        }
    } else {
        W(g, 0x750) = 0;
    }
    func_0026EBC0(s2, D_00427488, obj);
    func_0026EEF8(s2, obj, 0, 0, *(f32 *)(G + 0x750));

    a2 = 0;
    a0 = N(G, 0x114);
    a3 = W(G, 0x730);
    {
        u8 *v1 = N(a0, 0);
        if (v1 != 0) {
            do {
                a0 = v1;
                v1 = N(a0, 0);
            } while (v1 != 0);
        }
    }
    while (a0 != N(G, 0x114)) {
        a0 = N(a0, 8);
        a2++;
        if (a0 == 0) {
            break;
        }
    }
    f1 = (f32)a2;
    f2 = (f32)a3;
    f20 = (4.0f / f2) * 7.5f;
    f1 = (f1 * 240.0f) / f2;
    if (f1 >= 2147483648.0f) {
        v = (s32)(f1 - 2147483648.0f) | (s32)0x80000000;
    } else {
        v = (s32)f1;
    }
    func_0026EBC0(s2, D_00427498, obj);
    func_0026EF38(s2, obj, 0, 0, 1.0f, f20);
    func_0026EEC8(s2, obj, 0, v);
    func_0026EA58(G + 0x2C);
}
