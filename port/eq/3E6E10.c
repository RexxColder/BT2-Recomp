#include "common.h"

extern u8 *D_004279D0 __attribute__((section(".data")));
extern u8 D_00428A00[] __attribute__((section(".data")));
extern u8 D_00428A10[] __attribute__((section(".data")));
extern u8 D_00428A20[] __attribute__((section(".data")));
extern u8 D_00428A38[] __attribute__((section(".data")));
extern u8 D_00428A48[] __attribute__((section(".data")));
extern u8 D_00428A58[] __attribute__((section(".data")));
extern u8 D_00428A68[] __attribute__((section(".data")));
extern u8 D_00428A78[] __attribute__((section(".data")));
extern u8 D_00428A88[] __attribute__((section(".data")));
extern u8 D_00428AE8[] __attribute__((section(".data")));
extern u8 D_00428B00[] __attribute__((section(".data")));
extern u8 D_00428B10[] __attribute__((section(".data")));
extern u8 D_00428B28[] __attribute__((section(".data")));
extern u8 D_00428B68[] __attribute__((section(".data")));
extern u8 D_00428B78[] __attribute__((section(".data")));
extern u8 D_00428B90[] __attribute__((section(".data")));
extern u8 D_00428BA0[] __attribute__((section(".data")));
extern u8 D_00428BB0[] __attribute__((section(".data")));
extern u8 D_00428BC8[] __attribute__((section(".data")));

void func_00277E70(u8 *a0, s32 a1, s64 a2);
s32 func_0026EBC0(u8 *a0, u8 *a1, u8 *a2);
s32 func_0026EC48(u8 *a0, u8 *a1, u8 *a2);
s32 func_0026EFC8(u8 *a0, u8 *a1, s32 a2);
s32 func_0026EEC8(u8 *a0, u8 *a1, s32 a2, s32 a3);
void func_0026EEF8(u8 *a0, u8 *a1, s32 a2, s32 a3, f32 f12);
s32 func_0026EC18(u8 *a0, u8 *a1, s32 a2);
f32 func_0026F148(u8 *a0, u8 *a1);
s32 func_0026EA58(u8 *a0);
void func_0026EC78(u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, s32 t1, s32 t2, s32 t3);
void func_00249FB8(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
void func_002495A8(u8 *a0, u8 *a1, u8 *a2, s32 a3);
void func_00249778(u8 *a0, u8 *a1, u8 *a2, s32 a3);
extern s32 func_00325830();

#define RECT(x, y, x2, y2) do { \
    *(s32 *)(sp + 0x10) = (x); *(s32 *)(sp + 0x14) = (y); \
    *(s32 *)(sp + 0x18) = (x2); *(s32 *)(sp + 0x1C) = (y2); } while (0)
#define G (D_004279D0)

/* Menu screen draw (memory card style UI): G = D_004279D0, objects at G+0x10, sp = handle, sp+0x10 = rect. */
s32 func_003E6E10(void) {
    u8 sp[0x110];
    u8 *s1;
    u8 *s0;
    s32 i;
    s32 n;
    f32 f20;

    func_00277E70(*(u8 **)(G + 0x38), 0, 0x80);
    s1 = G + 0x10;
    func_0026EBC0(s1, D_00428A00, sp);
    func_0026EEF8(s1, sp, 0, 0, *(f32 *)(G + 0x30C));
    func_00249FB8(s1, sp, 0, 0, *(s32 *)(G + 8), *(s32 *)(G + 0xEC), 0);
    func_0026EBC0(s1, D_00428A10, sp);
    func_002495A8(s1, sp, G + 0x310, 1);
    func_0026EBC0(s1, D_00428A20, sp);
    func_00249778(s1, sp, G + 0x314, 3);

    i = 0;
    do {
        n = i + 1;
        func_00325830(sp + 0x30, D_00428A38, n);
        func_0026EBC0(s1, sp + 0x30, sp);
        RECT(0, i << 5, 0x200, (i << 5) + 0x20);
        func_0026EC48(s1, sp, sp + 0x10);
        if (*(s32 *)(G + 0xF4) == i) {
            func_0026EFC8(s1, sp, 8);
        } else {
            func_0026EFC8(s1, sp, 4);
        }
        i = n;
    } while (i < 4);

    __builtin_memcpy(sp + 0x50, D_00428A48, 16);
    __builtin_memcpy(sp + 0x60, D_00428A58, 16);
    RECT(0, *(s32 *)(G + 0xF4) << 5, 0x200, (*(s32 *)(G + 0xF4) << 5) + 0x20);
    func_0026EBC0(s1, D_00428A68, sp);
    func_0026EC48(s1, sp, sp + 0x10);
    func_0026EBC0(s1, D_00428A78, sp);
    n = *(s32 *)(G + 0xF4) << 2;
    func_0026EEC8(s1, sp, *(s32 *)(sp + 0x50 + n), *(s32 *)(sp + 0x60 + n));
    if (*(s32 *)(G + 0xF0) & 0xE) {
        func_0026EFC8(s1, sp, 2);
    } else {
        func_0026EFC8(s1, sp, 1);
    }

    __builtin_memcpy(sp + 0x70, D_00428A88, 0x60);
    s0 = sp + 0x70;
    i = 0;
    do {
        RECT(0, i << 6, 0x40, (i << 6) + 0x40);
        func_0026EBC0(s1, s0, sp);
        s0 += 0x20;
        if ((*(s32 *)(G + 0xF0) & 0xE) || *(s32 *)(G + 0xF4) != i) {
            func_0026EC48(s1, sp, sp + 0x10);
        } else {
            func_0026EC78(s1, sp, G + 0x2FC, G + 0x300, sp + 0x10, 4, 1, 6);
        }
        i++;
    } while (i < 3);

    RECT(0x10, 0, 0x20, 0x20);
    func_0026EBC0(s1, D_00428AE8, sp);
    func_0026EC48(s1, sp, sp + 0x10);
    n = *(s32 *)(G + 0xF8);
    RECT(0, n * 40, 0x200, n * 40 + 0x28);
    func_0026EBC0(s1, D_00428B00, sp);
    func_0026EC48(s1, sp, sp + 0x10);
    func_0026EBC0(s1, D_00428B10, sp);
    func_0026EEF8(s1, sp, 0, 0, *(f32 *)(G + 0x308));
    s0 = G;
    if (*(s32 *)(s0 + 0xF0) & 0x10) {
        func_0026EC18(s1, sp, *(s32 *)(s0 + 0x304));
    } else {
        func_0026EC18(s1, sp, *(s32 *)(s0 + 0xF8));
    }

    __builtin_memcpy(sp + 0xD0, D_00428B28, 0x40);
    s0 = sp + 0xD0;
    i = 0;
    do {
        RECT(0, i << 6, 0x100, (i << 6) + 0x40);
        func_0026EBC0(s1, s0, sp);
        s0 += 0x20;
        func_0026EC48(s1, sp, sp + 0x10);
        if (*(s32 *)(G + 0xF8) == i) {
            func_0026EFC8(s1, sp, 8);
            if ((*(s32 *)(G + 0xF0) & 4) == 0) {
                i++;
                f20 = func_0026F148(s1, sp);
                func_0026EBC0(s1, D_00428B68, sp);
                func_0026EEF8(s1, sp, 0, 0, f20);
                continue;
            }
        } else {
            func_0026EFC8(s1, sp, 4);
        }
        i++;
    } while (i < 2);

    n = *(s32 *)(G + 0xF8);
    RECT(0, n << 6, 0x100, (n << 6) + 0x40);
    func_0026EBC0(s1, D_00428B78, sp);
    func_0026EC48(s1, sp, sp + 0x10);
    func_0026EBC0(s1, D_00428B68, sp);
    func_0026EEC8(s1, sp, (*(s32 *)(G + 0xF8) != 1) ? 0 : 0xB6, 0);

    __builtin_memcpy(sp + 0x50, D_00428B90, 12);
    __builtin_memcpy(sp + 0x60, D_00428BA0, 12);
    {
        s32 x, y;
        n = *(s32 *)(G + 0x188) << 2;
        x = *(s32 *)(sp + 0x50 + n);
        y = *(s32 *)(sp + 0x60 + n);
        RECT(x, y, x + 0x40, y + 0x20);
    }
    func_0026EBC0(s1, D_00428BB0, sp);
    func_0026EC48(s1, sp, sp + 0x10);
    n = *(s32 *)(G + 0x18C) << 6;
    RECT(n, 0, n + 0x40, 0x20);
    func_0026EBC0(s1, D_00428BC8, sp);
    func_0026EC48(s1, sp, sp + 0x10);
    return func_0026EA58(G + 0x10);
}
