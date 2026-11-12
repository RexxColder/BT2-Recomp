#include "common.h"

extern u8 *D_0042A580 __attribute__((section(".data")));
extern u8 D_0042B2E0[] __attribute__((section(".data")));
extern u8 D_0042B2F0[] __attribute__((section(".data")));
extern u8 D_0042B300[] __attribute__((section(".data")));
extern u8 D_0042B310[] __attribute__((section(".data")));
extern u8 D_0042B328[] __attribute__((section(".data")));
extern u8 D_0042B340[] __attribute__((section(".data")));
extern u8 D_0042B350[] __attribute__((section(".data")));
extern u8 D_0042B368[] __attribute__((section(".data")));
extern u8 D_0042B380[] __attribute__((section(".data")));
extern u8 D_0042B398[] __attribute__((section(".data")));
extern u8 D_0042B3A8[] __attribute__((section(".data")));

void func_277E70(u8 *a0, s32 a1, s32 a2);
void func_26EBC0(u8 *a0, u8 *a1, u8 *a2);
void func_26EC48(u8 *a0, u8 *a1, u8 *a2);
void func_26EC18(u8 *a0, u8 *a1, s32 a2);
void func_26EFC8(u8 *a0, u8 *a1, s32 a2);
void func_26EEC8(u8 *a0, u8 *a1, s32 a2, s32 a3);
void func_26ED60(u8 *a0, u8 *a1, u8 *a2, u8 *a3, s32 a4, f32 f12, f32 f13);
void func_249778(u8 *a0, u8 *a1, u8 *a2, s32 a3);
void func_249FB8(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_24A598(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_26EA58(u8 *a0);
s32 func_24C060(u8 *a0);

s32 func_003F9B80(void) {
    u8 *a;
    u8 *p1;
    u8 *s1;
    u8 *s4;
    u8 sp[0x80];
    s32 s2;
    s32 v;
    s32 i;

    a = D_0042A580;
    func_277E70(*(u8 **)(a + 0x8C), 0, 0x80);

    a = D_0042A580;
    p1 = a + 0x64;
    func_26EBC0(p1, D_0042B2E0, sp);
    func_249778(p1, sp, a + 0xEC, 1);
    func_26EBC0(p1, D_0042B2F0, sp);
    func_249FB8(p1, sp, 0, 0, *(s32 *)(a + 0x8), *(s32 *)(a + 0xD8), 1);
    func_26EBC0(p1, D_0042B300, sp);
    func_24A598(p1, sp, 0, 0x10, *(s32 *)(a + 0x10), *(s32 *)(a + 0xDC) + 0x4D, 1);

    s4 = sp + 0x10;
    for (s2 = 0; s2 < 2; s2++) {
        u8 *a1 = (s2 != 0) ? D_0042B310 : D_0042B328;

        *(s32 *)(sp + 0x1C) = (32 * s2) + 0x20;
        *(s32 *)(sp + 0x14) = 32 * s2;
        *(s32 *)(sp + 0x10) = 0;
        *(s32 *)(sp + 0x18) = 0x200;
        func_26EBC0(p1, a1, sp);
        func_26EC48(p1, sp, s4);
    }

    a = D_0042A580;
    *(s32 *)(sp + 0x18) = 0x200;
    *(s32 *)(sp + 0x10) = 0;
    v = *(s32 *)(a + 0xD4) << 5;
    *(s32 *)(sp + 0x14) = v;
    *(s32 *)(sp + 0x1C) = v + 0x20;
    func_26EBC0(p1, D_0042B340, sp);
    func_26EC48(p1, sp, s4);

    func_26EBC0(p1, D_0042B350, sp);

    a = D_0042A580;
    v = *(s32 *)(a + 0xD4);
    func_26EEC8(p1, sp, 0, 70 * v);
    func_26EC18(p1, sp, 1);

    a = D_0042A580;
    if ((*(s32 *)(a + 0xD0) & 4) != 0) {
        *(s32 *)(sp + 0x1C) = 0x20;
    } else {
        *(s32 *)(sp + 0x1C) = 0x40;
    }
    *(s32 *)(sp + 0x18) = 0x100;
    *(s32 *)(sp + 0x14) = 0;
    *(s32 *)(sp + 0x10) = 0;
    func_26EBC0(p1, D_0042B368, sp);
    func_26EC48(p1, sp, s4);

    *(s32 *)(sp + 0x1C) = 0x60;
    *(s32 *)(sp + 0x18) = 0x100;
    *(s32 *)(sp + 0x14) = 0x40;
    *(s32 *)(sp + 0x10) = 0;
    func_26EBC0(p1, D_0042B380, sp);
    func_26EC48(p1, sp, s4);

    a = D_0042A580;
    if ((*(s32 *)(a + 0xD0) & 4) != 0) {
        func_26EFC8(p1, sp, 8);
    } else {
        func_26EFC8(p1, sp, 4);
    }

    s1 = a + 0x14;
    *(s32 *)(sp + 0x1C) = 0x80;
    *(s32 *)(sp + 0x18) = 0x200;
    *(s32 *)(sp + 0x14) = 0;
    *(s32 *)(sp + 0x10) = 0;
    func_26EBC0(s1, D_0042B398, sp);

    func_26ED60(s1, sp, s4, a + 0xF0, 0, 1.0f, 0.0f);
    func_26EBC0(s1, D_0042B3A8, sp);
    func_26EFC8(s1, sp, 0x80);

    /* loop of three entries; the asm reloads a0 from D_0042A580 on each continue */
    for (i = 0; i < 3; i++) {
        func_26EA58(a + 0x14 + 0x28 * i);
    }
    return func_24C060(a + 0x64);
}
