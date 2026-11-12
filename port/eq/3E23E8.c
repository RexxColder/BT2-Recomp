#include "common.h"

extern u8 *D_004279C8 __attribute__((section(".data")));
extern u8 D_00427AE0[] __attribute__((section(".data")));
extern u8 D_00427AF0[] __attribute__((section(".data")));
extern u8 D_00427B10[] __attribute__((section(".data")));
extern u8 D_00427B28[] __attribute__((section(".data")));
extern u8 D_00427B38[] __attribute__((section(".data")));
extern u8 D_00427B48[] __attribute__((section(".data")));
extern u8 D_00427B58[] __attribute__((section(".data")));
extern u8 D_00427B70[] __attribute__((section(".data")));
extern u8 D_00427B90[] __attribute__((section(".data")));
extern u8 D_00427BA8[] __attribute__((section(".data")));
extern u8 D_00427BB8[] __attribute__((section(".data")));
extern u8 D_00427BC8[] __attribute__((section(".data")));
extern u8 D_00427BD8[] __attribute__((section(".data")));
extern u8 D_00427BF0[] __attribute__((section(".data")));

s32 func_00277E70(void *a0, s32 a1, s64 a2);
void func_0026EBC0(u8 *a0, u8 *a1, u8 *a2);
void func_00249FB8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, s32 arg6);
void func_0026EC48(u8 *a0, u8 *a1, u8 *a2);
void func_0026EFC8(u8 *a0, u8 *a1, s32 a2);
void func_0026EEC8(u8 *a0, u8 *a1, s32 a2, s32 a3);
void func_0026EA58(u8 *a0);
s32 func_00325830(u8 *buf, u8 *fmt, ...);

#define F(off) (*(s32 *)(D_004279C8 + (off)))
#define P(sp, a, b, c, d) do { *(s32 *)((sp) + 0x10) = (a); *(s32 *)((sp) + 0x14) = (b); \
    *(s32 *)((sp) + 0x18) = (c); *(s32 *)((sp) + 0x1C) = (d); } while (0)

/* 0x003E23E8: menu (memory-card/controller select) draw. g = *D_004279C8; obj = g + 0x10.
   sp[0..] = name block, sp+0x10 = 4-word rect param block */
void func_003E23E8(void) {
    u8 sp[0xE0];
    u8 *obj;
    s32 i, t, x, y, v;

    func_00277E70(*(u8 **)(D_004279C8 + 0x38), 0, 0x80);
    obj = D_004279C8 + 0x10;
    func_0026EBC0(obj, D_00427AE0, sp);
    func_00249FB8(obj, sp, 0, 0, *(u8 **)(D_004279C8 + 8), F(0xBC), 0);

    i = 0;
    do {
        s32 n = i + 1;
        P(sp, 0, i * 32, 64, i * 32 + 32);
        func_00325830(sp + 0x30, D_00427AF0, n);
        func_0026EBC0(obj, sp + 0x30, sp);
        if (F(0xC4) == i) {
            func_0026EFC8(obj, sp, 8);
        } else {
            func_0026EFC8(obj, sp, 4);
            func_0026EC48(obj, sp, sp + 0x10);
        }
        i = n;
    } while (i < 2);

    v = F(0xC4) << 6;
    P(sp, v, 0, v + 64, 64);
    func_0026EBC0(obj, D_00427B10, sp);
    func_0026EC48(obj, sp, sp + 0x10);
    func_0026EEC8(obj, sp, F(0xC4) * 60, 0);
    if (F(0xC0) & 1) {
        func_0026EFC8(obj, sp, 2);
    } else {
        func_0026EFC8(obj, sp, 1);
    }

    i = 0;
    do {
        s32 n = i + 1;
        P(sp, 0, i * 32, 256, i * 32 + 32);
        func_00325830(sp + 0x50, D_00427B28, n);
        func_0026EBC0(obj, sp + 0x50, sp);
        if (F(0xC8) == i && (F(0xC0) & 1)) {
            func_0026EFC8(obj, sp, 8);
        } else {
            func_0026EFC8(obj, sp, 4);
            func_0026EC48(obj, sp, sp + 0x10);
        }
        i = n;
    } while (i < 3);

    v = F(0xC8) * 32;
    P(sp, 0, v, 256, v + 32);
    func_0026EBC0(obj, D_00427B38, sp);
    func_0026EC48(obj, sp, sp + 0x10);
    func_0026EBC0(obj, D_00427B48, sp);
    if (F(0xC0) & 1) {
        func_0026EFC8(obj, sp, 4);
        func_0026EEC8(obj, sp, (F(0xC8) == 2) ? 106 : 0, F(0xC8) * 38);
    } else {
        func_0026EFC8(obj, sp, 8);
    }

    P(sp, 16, 0, 32, 32);
    func_0026EBC0(obj, D_00427B58, sp);
    func_0026EC48(obj, sp, sp + 0x10);
    func_0026EBC0(obj, D_00427B70, sp);
    if (F(0xC0) & 1) {
        if (F(0xC8) == 0) {
            func_0026EFC8(obj, sp, 4);
            func_0026EEC8(obj, sp, 0, 0);
            *(s32 *)(sp + 0x10) = 0;
        } else if (F(0xC8) == 1) {
            func_0026EFC8(obj, sp, 4);
            func_0026EEC8(obj, sp, 0, 0x26);
            *(s32 *)(sp + 0x10) = 0;
        } else {
            func_0026EFC8(obj, sp, 8);
            *(s32 *)(sp + 0x10) = 0;
        }
    } else {
        func_0026EFC8(obj, sp, 8);
        *(s32 *)(sp + 0x10) = 0;
    }

    {
        u8 *g = D_004279C8;
        v = *(s32 *)(g + 0x1F0 + F(0xC4) * 4) * 32;
        *(s32 *)(sp + 0x18) = 0x80;
        *(s32 *)(sp + 0x14) = v;
        func_0026EBC0(obj, D_00427B90, sp);
        *(s32 *)(sp + 0x1C) = v + 32;
        func_0026EC48(obj, sp, sp + 0x10);
    }
    {
        u8 *g = D_004279C8;
        s32 c4 = *(s32 *)(g + 0xC4);
        if (c4 == 0) {
            *(s32 *)(sp + 0x14) = (*(s32 *)(g + 0x16C) << 4) & 0x20;
        } else if (c4 == 1) {
            *(s32 *)(sp + 0x14) = (*(s32 *)(g + 0x16C) << 3) & 0x20;
        } else {
            *(s32 *)(sp + 0x14) = 0;
        }
    }
    *(s32 *)(sp + 0x18) = 0x40;
    *(s32 *)(sp + 0x10) = 0;
    *(s32 *)(sp + 0x1C) = *(s32 *)(sp + 0x14) + 0x20;
    if ((F(0xC0) & 1) && F(0xC8) == 1) {
        func_0026EBC0(obj, D_00427BA8, sp);
        func_0026EFC8(obj, sp, 8);
        func_0026EBC0(obj, D_00427BB8, sp);
        func_0026EC48(obj, sp, sp + 0x10);
        func_0026EFC8(obj, sp, 4);
    } else {
        func_0026EBC0(obj, D_00427BB8, sp);
        func_0026EFC8(obj, sp, 8);
        func_0026EBC0(obj, D_00427BA8, sp);
        func_0026EC48(obj, sp, sp + 0x10);
        func_0026EFC8(obj, sp, 4);
    }

    P(sp, 0x30, 0, 0x60, 0xA0);
    func_0026EBC0(obj, D_00427BC8, sp);
    func_0026EC48(obj, sp, sp + 0x10);
    func_0026EBC0(obj, D_00427BD8, sp);

    {
        u8 *g = D_004279C8;
        if ((*(s32 *)(g + 0xC0) & 1) && *(s32 *)(g + 0xC8) == 0 &&
            *(s32 *)(g + 0x1F0 + *(s32 *)(g + 0xC4) * 4) == 5) {
            s32 m = *(s32 *)(g + 0x36C);
            if (m == -1) {
                func_0026EFC8(obj, sp, 8);
            } else {
                if ((u32)m < 8) {
                    switch (m) {
                    case 0: *(s32 *)(sp + 0x10) = 0x30; *(s32 *)(sp + 0x14) = 0x50; break;
                    case 1: *(s32 *)(sp + 0x10) = 0x30; *(s32 *)(sp + 0x14) = 0x78; break;
                    case 2: *(s32 *)(sp + 0x10) = 0;    *(s32 *)(sp + 0x14) = 0x78; break;
                    case 3: *(s32 *)(sp + 0x10) = 0;    *(s32 *)(sp + 0x14) = 0x50; break;
                    case 4: *(s32 *)(sp + 0x10) = 0;    *(s32 *)(sp + 0x14) = 0x28; break;
                    case 5: *(s32 *)(sp + 0x10) = 0;    *(s32 *)(sp + 0x14) = 0; break;
                    case 6: *(s32 *)(sp + 0x10) = 0x30; *(s32 *)(sp + 0x14) = 0x28; break;
                    case 7: *(s32 *)(sp + 0x10) = 0x30; *(s32 *)(sp + 0x14) = 0; break;
                    }
                }
                x = *(s32 *)(sp + 0x10);
                y = *(s32 *)(sp + 0x14);
                *(s32 *)(sp + 0x18) = x + 0x30;
                *(s32 *)(sp + 0x1C) = y + 0x28;
                func_0026EEC8(obj, sp, (0 < x) ? 0xB4 : 0, y);
                func_0026EC48(obj, sp, sp + 0x10);
                func_0026EFC8(obj, sp, 4);
                func_0026EBC0(obj, D_00427B70, sp);
                x = *(s32 *)(sp + 0x10);
                y = *(s32 *)(sp + 0x14);
                func_0026EEC8(obj, sp, (0 < x) ? 0x1A : -0x9A, y - 0x9F);
            }
        } else {
            func_0026EFC8(obj, sp, 8);
        }
    }

    t = 0;
    do {
        s32 k, w;
        u8 *g;
        func_00325830(sp + 0x70, D_00427BF0, t);
        func_0026EBC0(obj, sp + 0x70, sp);
        switch ((u32)t) {
        case 0: k = 5; break;
        case 1: k = 4; break;
        case 2: k = 7; break;
        case 3: k = 6; break;
        case 4: k = 3; break;
        case 5: k = 2; break;
        case 7: k = 1; break;
        default: k = 0; break;
        }
        g = D_004279C8;
        v = *(s32 *)(g + 0xC4);
        if (*(s32 *)(g + 0x1F0 + v * 4) == 5) {
            w = *(s32 *)(g + 0x1B0 + (v * 8 + k) * 4);
        } else {
            w = *(s32 *)(g + 0xCC + (*(s32 *)(g + 0x1F0 + v * 4) * 8 + k) * 4);
        }
        switch ((u32)w) {
        case 0: *(s32 *)(sp + 0x10) = 0x80; *(s32 *)(sp + 0x14) = 0x28; break;
        case 1: *(s32 *)(sp + 0x10) = 0x80; *(s32 *)(sp + 0x14) = 0x78; break;
        case 2: *(s32 *)(sp + 0x10) = 0x80; *(s32 *)(sp + 0x14) = 0x50; break;
        case 3: *(s32 *)(sp + 0x10) = 0x80; *(s32 *)(sp + 0x14) = 0; break;
        case 5: *(s32 *)(sp + 0x10) = 0; *(s32 *)(sp + 0x14) = 0x28; break;
        case 6: *(s32 *)(sp + 0x10) = 0; *(s32 *)(sp + 0x14) = 0x50; break;
        case 7: *(s32 *)(sp + 0x10) = 0; *(s32 *)(sp + 0x14) = 0x78; break;
        default: *(s32 *)(sp + 0x10) = 0; *(s32 *)(sp + 0x14) = 0; break;
        }
        *(s32 *)(sp + 0x1C) = *(s32 *)(sp + 0x14) + 0x28;
        *(s32 *)(sp + 0x18) = *(s32 *)(sp + 0x10) + 0x80;
        t++;
        func_0026EC48(obj, sp, sp + 0x10);
    } while (t < 8);

    {
        u8 *g = D_004279C8;
        if ((*(s32 *)(g + 0xC0) & 1) && *(s32 *)(g + 0xC8) == 0 &&
            *(s32 *)(g + 0x1F0 + *(s32 *)(g + 0xC4) * 4) == 5) {
            *(s32 *)(g + 0x7C) = 0;
        } else {
            *(s32 *)(g + 0x7C) = *(s32 *)(*(u8 **)(g + 0x44) + 0x10);
        }
    }
    func_0026EA58(D_004279C8 + 0x10);
}
