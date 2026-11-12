#include "common.h"

extern u8 *D_00427338;
extern u8 D_00427928[];
extern u8 D_00427938[];
extern u8 D_00427948[];
extern u8 D_00427958[];
extern u8 D_00427968[];
extern u8 D_00427978[];
extern u8 D_00427990[];
extern u8 D_00427998[];
extern u8 D_004279A8[];
extern s32 func_00277E70();
extern s32 func_0026EBC0();
extern s32 func_0026EEC8();
extern s32 func_0026EC48();
extern s32 func_0026EFC8();
extern s32 func_00325830();
extern s32 func_0026EC18();
extern s32 func_0026EF38(u8 *a0, u8 *a1, f32 f12, f32 f13);
extern s32 func_002495A8();
extern s32 func_002498D8();
extern s32 func_0026EA58();

s32 func_003E0EC8(void) {
    u8 sp[0xB0];
    u8 *s6 = sp + 0x10;
    u8 *buf1 = sp + 0x30;
    u8 *buf2 = sp + 0x50;
    u8 *g;
    u8 *s1;
    s32 i;
    s32 n;
    s32 a;
    s32 x;
    s32 off;
    s32 r;
    s32 s2;
    f32 f0;
    f32 f20;

    g = D_00427338;
    func_00277E70(*(s32 *)(g + 0x70), 0, 0x80);
    s1 = D_00427338 + 8;
    func_0026EBC0(s1, D_00427928, sp);
    g = D_00427338;
    func_0026EEC8(s1, sp, 0, (*(s32 *)(g + 0xD4) - *(s32 *)(g + 0xD0)) * 34);
    *(s32 *)(sp + 0x1C) = 0x20;
    *(s32 *)(sp + 0x18) = 0x40;
    *(s32 *)(sp + 0x10) = 0x20;
    *(s32 *)(sp + 0x14) = 0;
    func_0026EBC0(s1, D_00427938, sp);
    func_0026EC48(s1, sp, s6);
    g = D_00427338;
    if (*(s32 *)(g + 0xD0) < *(s32 *)(g + 0xE8) - 8) {
        func_0026EFC8(s1, sp, 4);
    } else {
        func_0026EFC8(s1, sp, 8);
    }
    func_0026EBC0(s1, D_00427948, sp);
    g = D_00427338;
    if (*(s32 *)(g + 0xD0) > 0) {
        func_0026EFC8(s1, sp, 4);
    } else {
        func_0026EFC8(s1, sp, 8);
    }
    i = 0;
    do {
        *(s32 *)(sp + 0x14) = i << 5;
        *(s32 *)(sp + 0x1C) = (i << 5) + 0x20;
        *(s32 *)(sp + 0x10) = 0;
        *(s32 *)(sp + 0x18) = 0x100;
        func_00325830(buf1, D_00427958, i);
        func_0026EBC0(s1, buf1, sp);
        func_0026EC48(s1, sp, s6);
        g = D_00427338;
        if (*(s32 *)(g + 0xD8) == i) {
            func_0026EFC8(s1, sp, 8);
        } else {
            func_0026EFC8(s1, sp, 4);
        }
        i++;
    } while (i < 2);
    *(s32 *)(sp + 0x10) = 0;
    g = D_00427338;
    *(s32 *)(sp + 0x18) = 0x100;
    *(s32 *)(sp + 0x14) = *(s32 *)(g + 0xD8) << 5;
    *(s32 *)(sp + 0x1C) = (*(s32 *)(g + 0xD8) << 5) + 0x20;
    func_0026EBC0(s1, D_00427968, sp);
    func_0026EC48(s1, sp, s6);
    g = D_00427338;
    func_0026EEC8(s1, sp, *(s32 *)(g + 0xD8) * 175, 0);
    i = 0;
    *(s32 *)(sp + 0x10) = 0;
    do {
        g = D_00427338;
        n = *(s32 *)(*(u8 **)(g + 0xE4) + (*(s32 *)(g + 0xD0) + i) * 8 + 4);
        *(s32 *)(sp + 0x18) = 0x200;
        a = n - 1;
        *(s32 *)(sp + 0x14) = (a % 8) << 5;
        *(s32 *)(sp + 0x1C) = ((a % 8) << 5) + 0x20;
        func_00325830(buf2, D_00427978, i);
        func_0026EBC0(s1, buf2, sp);
        func_0026EEC8(s1, sp, -0x10, -8);
        g = D_00427338;
        off = (*(s32 *)(g + 0xD0) + i) * 8;
        if (*(s32 *)(g + 0xD4) - *(s32 *)(g + 0xD0) == i) {
            x = *(s32 *)(g + 0xE8) + 1;
            n = *(s32 *)(*(u8 **)(g + 0xE4) + off + 4);
            func_0026EC18(s1, sp, (n - 1) / 8 + x / 8 + ((x & 7) != 0));
        } else {
            n = *(s32 *)(*(u8 **)(g + 0xE4) + off + 4);
            func_0026EC18(s1, sp, (n - 1) / 8);
        }
        func_0026EC48(s1, sp, s6);
        i++;
        if (i < 8) {
            *(s32 *)(sp + 0x10) = 0;
        }
    } while (i < 8);
    g = D_00427338;
    f0 = (f32)*(s32 *)(g + 0xD0) * 296.0f;
    f20 = (8.0f / (f32)*(s32 *)(g + 0xE8)) * 9.25f;
    f0 = f0 / (f32)*(s32 *)(g + 0xE8);
    s2 = (s32)f0;
    if (f0 >= 2147483648.0f) {
        s2 = (s32)(f0 - 2147483648.0f) | (s32)0x80000000;
    }
    func_0026EBC0(s1, D_00427990, sp);
    func_0026EF38(s1, sp, 1.0f, f20);
    func_0026EEC8(s1, sp, 0, s2);
    g = D_00427338;
    s1 = g + 0x30;
    func_0026EBC0(s1, D_00427998, sp);
    g = D_00427338;
    if (*(s32 *)(g + 0xCC) & 4) {
        if (*(s32 *)(g + 0xE0) >= 0x29) {
            *(s32 *)(g + 0xE0) = 0x28;
        }
    }
    func_002495A8(s1, sp, D_00427338 + 0xE0, 1);
    func_0026EBC0(s1, D_004279A8, sp);
    func_002498D8(s1, sp, 3);
    off = 0;
    i = 1;
    r = 0;
    do {
        i--;
        r = func_0026EA58(D_00427338 + off + 8);
        off += 0x28;
    } while (i >= 0);
    return r;
}
