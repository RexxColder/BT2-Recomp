#include "common.h"

extern u8 *D_0042BB80 __attribute__((section(".data")));
extern u8 D_0042EF10[] __attribute__((section(".data")));
extern u8 D_0042EF38[] __attribute__((section(".data")));
extern u8 D_0042EF58[] __attribute__((section(".data")));
extern u8 D_0042EF78[] __attribute__((section(".data")));
extern u8 D_0042EFB8[] __attribute__((section(".data")));
extern u8 D_0042EFD0[] __attribute__((section(".data")));
extern u8 D_0042EFE8[] __attribute__((section(".data")));
extern u8 D_0042F000[] __attribute__((section(".data")));
extern u8 D_0042F028[] __attribute__((section(".data")));
extern u8 D_0042F040[] __attribute__((section(".data")));
extern u8 D_0042F0E0[] __attribute__((section(".data")));
extern u8 D_0042F0F0[] __attribute__((section(".data")));
extern u8 D_0042F100[] __attribute__((section(".data")));

extern s32 func_277E70();
extern s32 func_26EBC0();
extern s32 func_26EC48();
extern s32 func_26EC18();
extern s32 func_26EA58();
extern s32 func_00418CC8();
extern s32 func_00418E78();

/* 0x00419820: map screen layout. N = D_0042BB80, W = N+0x30. Loads the arrow / button icon parts and their rects
 * (20-byte rects copied from data tables to the stack), the break on/off rect (N->0xE0), the map name text
 * (index N->0xFC[N->0xD4] split into row/8 and rect %8), the bgm name text (N->0xD8 / list N->0x140), then seven
 * map icons (0x80-byte names from D_0042F100) whose frame is N->0xFC[(N->0xDC + i) % N->0x13C]. Resets N+8, and
 * calls func_00418CC8 (N->0xC4 == 2 and !(N->0xD0 & 4)) or func_00418E78, then resets N+0x30. */
s32 func_00419820(void) {
    u8 sp[0x4A0] __attribute__((aligned(16)));
    u8 *w;
    u8 *n;
    s32 i;
    s32 v;
    s32 a;
    u8 *t;

    func_277E70(*(s32 *)(D_0042BB80 + 0x58), 0, 0x80);
    w = D_0042BB80 + 0x30;
    __builtin_memcpy(sp + 0x10, D_0042EF10, 0x28);
    func_26EBC0(w, D_0042EF38, sp);
    func_26EC48(w, sp, sp + 0x10);
    func_26EBC0(w, D_0042EF58, sp);
    func_26EC48(w, sp, sp + 0x24);

    __builtin_memcpy(sp + 0x40, D_0042EF78, 0x3C);
    func_26EBC0(w, D_0042EFB8, sp);
    func_26EC48(w, sp, sp + 0x40);
    func_26EBC0(w, D_0042EFD0, sp);
    func_26EC48(w, sp, sp + 0x54);
    func_26EBC0(w, D_0042EFE8, sp);
    func_26EC48(w, sp, sp + 0x68);

    __builtin_memcpy(sp + 0x10, D_0042F000, 0x28);
    func_26EBC0(w, D_0042F028, sp);
    func_26EC48(w, sp, sp + 0x10 + *(s32 *)(D_0042BB80 + 0xE0) * 20);

    __builtin_memcpy(sp + 0x80, D_0042F040, 0xA0);
    func_26EBC0(w, D_0042F0E0, sp);
    n = D_0042BB80;
    v = *(s32 *)(n + *(s32 *)(n + 0xD4) * 4 + 0xFC);
    a = v < 0 ? v + 7 : v;
    func_26EC18(w, sp, a >> 3);
    n = D_0042BB80;
    v = *(s32 *)(n + *(s32 *)(n + 0xD4) * 4 + 0xFC);
    a = v < 0 ? v + 7 : v;
    func_26EC48(w, sp, sp + 0x80 + (v - (a >> 3 << 3)) * 20);

    func_26EBC0(w, D_0042F0F0, sp);
    n = D_0042BB80;
    if (*(s32 *)(n + 0xD8) == 0) {
        func_26EC18(w, sp, 4);
        func_26EC48(w, sp, sp + 0xA8);
    } else {
        v = *(s32 *)(*(u8 **)(n + 0x140) + *(s32 *)(n + 0xD8) * 8 - 4);
        a = v - 1;
        if (a < 0) {
            a = v + 6;
        }
        func_26EC18(w, sp, a >> 3);
        n = D_0042BB80;
        v = *(s32 *)(*(u8 **)(n + 0x140) + *(s32 *)(n + 0xD8) * 8 - 4);
        i = v - 1;
        a = i < 0 ? v + 6 : i;
        func_26EC48(w, sp, sp + 0x80 + (i - (a >> 3 << 3)) * 20);
    }

    __builtin_memcpy(sp + 0x120, D_0042F100, 0x380);
    t = sp + 0x120;
    i = 0;
    do {
        u8 *u = t;
        t += 0x80;
        func_26EBC0(w, u, sp);
        n = D_0042BB80;
        v = *(s32 *)(n + 0xDC) + i;
        a = *(s32 *)(n + 0x13C);
        i++;
        func_26EC18(w, sp, *(s32 *)(n + (v % a) * 4 + 0xFC));
    } while (i < 7);

    func_26EA58(D_0042BB80 + 8);
    n = D_0042BB80;
    if (*(s32 *)(n + 0xC4) != 2 || (*(s32 *)(n + 0xD0) & 4) != 0) {
        func_00418E78();
    } else {
        func_00418CC8();
    }
    return func_26EA58(D_0042BB80 + 0x30);
}
