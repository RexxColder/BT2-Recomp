#include "common.h"

extern u8 *D_0042A584 __attribute__((section(".data")));
extern u8 *D_00387F2C;
extern u8 D_0042B5B0[];
extern u8 D_0042B5B8[];
extern u8 D_0042B5C8[];
extern u8 D_0042B5D8[];
extern u8 D_0042B5E8[];
extern u8 D_0042B5F8[];
extern u8 D_0042B608[];
extern u8 D_0042B618[];
extern u8 D_0042B628[];
extern u8 D_0042B638[];
extern u8 D_0042B650[];
extern s32 func_00277E70();
extern s32 func_0026EBC0();
extern s32 func_0026EFC8();
extern s32 func_0026ED60(u8 *a0, u8 *a1, u8 *a2, u8 *a3, s32 t0, f32 f12, f32 f13);
extern s32 func_0026EC48();
extern s32 func_00249778();
extern s32 func_00325830();
extern s32 func_00249A98();
extern s32 func_0024A598();
extern s32 func_003FA6B0();
extern s32 func_0026EA58();

#define IDX(g) (*(s32 *)((g) + *(s32 *)((g) + 0x110) * 4 + 0x114))

s32 func_003FAD88(void) {
    u8 sp[0xB0];
    u8 *g;
    u8 *s2;
    u8 *s7 = sp + 0x10;
    u8 *buf = sp + 0x30;
    s32 v0;
    s32 i;
    s32 s0;
    s32 s5;
    s32 n;
    s32 off;
    s32 t0;
    u8 *p;
    s32 r;

    g = D_0042A584;
    func_00277E70(*(s32 *)(g + 0x64), 0, 0x80);
    s2 = D_0042A584 + 0x14;
    func_0026EBC0(s2, D_0042B5B0, sp);
    func_0026EFC8(s2, sp, 0x80);
    *(s32 *)(sp + 0x1C) = 0x80;
    *(s32 *)(sp + 0x14) = 0;
    *(s32 *)(sp + 0x10) = 0;
    *(s32 *)(sp + 0x18) = 0x200;
    func_0026EBC0(s2, D_0042B5B8, sp);
    func_0026ED60(s2, sp, s7, D_0042A584 + 0x128, 0, 1.0f, 0.0f);
    s2 = D_0042A584 + 0x3C;
    func_0026EBC0(s2, D_0042B5C8, sp);
    func_00249778(s2, sp, D_0042A584 + 0x120, 1);
    g = D_0042A584;
    *(s32 *)(sp + 0x10) = 0;
    v0 = *(s32 *)(g + 0x110);
    *(s32 *)(sp + 0x18) = 0x200;
    *(s32 *)(sp + 0x14) = v0 << 5;
    *(s32 *)(sp + 0x1C) = (v0 << 5) + 0x20;
    func_0026EBC0(s2, D_0042B5D8, sp);
    func_0026EC48(s2, sp, s7);
    *(s32 *)(sp + 0x18) = 0x20;
    *(s32 *)(sp + 0x1C) = 0x40;
    *(s32 *)(sp + 0x14) = 0x20;
    *(s32 *)(sp + 0x10) = 0;
    func_0026EBC0(s2, D_0042B5E8, sp);
    func_0026EC48(s2, sp, s7);
    g = D_0042A584;
    if (IDX(g) + 5 < 15) {
        func_0026EFC8(s2, sp, 4);
    } else {
        func_0026EFC8(s2, sp, 8);
    }
    func_0026EBC0(s2, D_0042B5F8, sp);
    g = D_0042A584;
    if (IDX(g) > 0) {
        func_0026EFC8(s2, sp, 4);
    } else {
        func_0026EFC8(s2, sp, 8);
    }
    s5 = 0;
    i = 0;
    do {
        s0 = i + 1;
        func_00325830(buf, D_0042B608, s0);
        func_0026EBC0(s2, buf, sp);
        g = D_0042A584;
        *(s32 *)(sp + 0x10) = 0;
        t0 = 0x40;
        v0 = *(s32 *)(*(u8 **)(g + 0x130) + (IDX(g) + i) * 56 + 0xC);
        *(s32 *)(sp + 0x18) = 0x80;
        if (v0 == 2) {
            t0 = 0;
        }
        *(s32 *)(sp + 0x14) = t0;
        *(s32 *)(sp + 0x1C) = t0 + 0x40;
        func_0026EC48(s2, sp, s7);
        g = D_0042A584;
        off = (*(s32 *)(g + 0x110) * 15 + IDX(g) + i) * 4;
        if (*(u16 *)(D_00387F2C + off + 0x20E) != 0) {
            func_0026EFC8(s2, sp, 4);
        } else {
            func_0026EFC8(s2, sp, 8);
        }
        func_00325830(buf, D_0042B618, s0);
        func_0026EBC0(s2, buf, sp);
        g = D_0042A584;
        func_00249A98(s2, sp, 0, 0, IDX(g) + i + 1, 0);
        func_00325830(buf, D_0042B628, s0);
        func_0026EBC0(s2, buf, sp);
        g = D_0042A584;
        func_0024A598(s2, sp, 0, 0, *(s32 *)(g + 8), IDX(g) + i + 0x52, 0);
        func_00325830(buf, D_0042B638, s0);
        func_0026EBC0(s2, buf, sp);
        g = D_0042A584;
        off = (*(s32 *)(g + 0x110) * 15 + IDX(g) + i) * 4;
        i = s0;
        func_00249A98(s2, sp, 0, 0, *(u16 *)(D_00387F2C + off + 0x20E) * 100, 2);
    } while (i < 5);
    func_003FA6B0();
    n = 14;
    g = D_0042A584;
    p = D_00387F2C + *(s32 *)(g + 0x110) * 60 + 0x20E;
    do {
        v0 = *(u16 *)p;
        p += 4;
        n--;
        s5 += v0;
    } while (n >= 0);
    func_0026EBC0(s2, D_0042B650, sp);
    func_00249A98(s2, sp, 0, 0, s5 * 100, 2);
    off = 0;
    n = 1;
    r = 0;
    do {
        n--;
        g = D_0042A584;
        r = func_0026EA58(g + off + 0x14);
        off += 0x28;
    } while (n >= 0);
    return r;
}
