#include "common.h"

extern u8 *D_00427334 __attribute__((section(".data")));
extern u8 D_004275E8[] __attribute__((section(".data")));
extern u8 D_004275F8[] __attribute__((section(".data")));
extern u8 D_00427608[] __attribute__((section(".data")));
extern u8 D_00427618[] __attribute__((section(".data")));
extern u8 D_004276D8[] __attribute__((section(".data")));
extern u8 D_004276F0[] __attribute__((section(".data")));
extern u8 D_00427708[] __attribute__((section(".data")));
extern u8 D_00427718[] __attribute__((section(".data")));
extern u8 D_00427730[] __attribute__((section(".data")));
extern u8 D_00427740[] __attribute__((section(".data")));
extern u8 D_00427800[] __attribute__((section(".data")));

extern s32 func_277E70();
extern s32 func_26EBC0();
extern s32 func_2495A8();
extern s32 func_249778();
extern s32 func_249FB8();
extern s32 func_26EC48();
extern s32 func_26EFC8();
extern s32 func_26EC78();
extern s32 func_26EEC8();
extern s32 func_26EA58();
extern s32 func_24C060();

/* 0x003E0040: menu (zukan) layout setup. N = D_00427334, W = N+0x38 (layout object). Loads the parts
 * mcGuideEye/mcGuideMouth/mc_textwindow, three text tabs (64-byte names copied from the 0xC0 table
 * D_00427618; the one equal to N->0x9C is highlighted: flag 8, else 4), the on-anime text/icon/menu_on, three
 * badges (D_00427740) and three icons (D_00427800), then resets two sub-objects (N+0x10, N+0x38) and calls func_24C060. */
s32 func_003E0040(void) {
    u8 sp[0x2A0] __attribute__((aligned(16)));
    u8 *t;
    u8 *u;
    s32 i;
    s32 v;
    u8 *w;

    func_277E70(*(s32 *)(D_00427334 + 0x60), 0, 0x80);
    w = D_00427334 + 0x38;
    func_26EBC0(w, D_004275E8, sp);
    func_2495A8(w, sp, D_00427334 + 0xAC, 1);
    func_26EBC0(w, D_004275F8, sp);
    func_249778(w, sp, D_00427334 + 0xB0, 3);
    func_26EBC0(w, D_00427608, sp);
    func_249FB8(w, sp, 0, 0, *(s32 *)(D_00427334 + 8), *(s32 *)(D_00427334 + 0xA0), 1);

    __builtin_memcpy(sp + 0x30, D_00427618, 0xC0);
    t = sp + 0x30;
    i = 0;
    v = 0;
    do {
        u = t;
        *(s32 *)(sp + 0x1C) = v + 0x20;
        *(s32 *)(sp + 0x14) = v;
        t += 0x40;
        *(s32 *)(sp + 0x10) = 0;
        *(s32 *)(sp + 0x18) = 0x100;
        func_26EBC0(w, u, sp);
        func_26EC48(w, sp, sp + 0x10);
        if (*(s32 *)(D_00427334 + 0x9C) != i) {
            i++;
            func_26EFC8(w, sp, 4);
        } else {
            i++;
            func_26EFC8(w, sp, 8);
        }
        v = i << 5;
    } while (i < 3);

    v = *(s32 *)(D_00427334 + 0x9C) << 6;
    *(s32 *)(sp + 0x18) = 0x100;
    *(s32 *)(sp + 0x10) = 0;
    *(s32 *)(sp + 0x14) = v;
    *(s32 *)(sp + 0x1C) = v + 0x40;
    func_26EBC0(w, D_004276D8, sp);
    func_26EC48(w, sp, sp + 0x10);

    __builtin_memcpy(sp + 0xF0, D_004276F0, 0x14);
    __builtin_memcpy(sp + 0x110, D_00427708, 0xC);
    v = *(s32 *)(D_00427334 + 0x9C) << 6;
    *(s32 *)(sp + 0xF8) = 0x40;
    *(s32 *)(sp + 0xF0) = 0;
    *(s32 *)(sp + 0xF4) = v;
    *(s32 *)(sp + 0xFC) = v + 0x40;
    func_26EBC0(w, D_00427718, sp);
    func_26EC78(w, sp, D_00427334 + 0xB4, D_00427334 + 0xB8, sp + 0xF0,
                *(s32 *)(sp + 0x110 + (*(s32 *)(D_00427334 + 0x9C) << 2)), 1, 6);
    func_26EBC0(w, D_00427730, sp);
    func_26EEC8(w, sp, 0, *(s32 *)(D_00427334 + 0x9C) * 58);

    __builtin_memcpy(sp + 0x120, D_00427740, 0xC0);
    t = sp + 0x120;
    i = 0;
    do {
        u = t;
        t += 0x40;
        func_26EBC0(w, u, sp);
        v = (i ^ *(s32 *)(D_00427334 + 0x9C)) != 0 ? 4 : 8;
        i++;
        func_26EFC8(w, sp, v);
    } while (i < 3);

    __builtin_memcpy(sp + 0x1E0, D_00427800, 0xC0);
    i = 0;
    do {
        v = i << 6;
        *(s32 *)(sp + 0x1C) = v + 0x40;
        *(s32 *)(sp + 0x14) = v;
        *(s32 *)(sp + 0x10) = 0;
        *(s32 *)(sp + 0x18) = 0x40;
        func_26EBC0(w, sp + 0x1E0 + v, sp);
        func_26EC48(w, sp, sp + 0x10);
        v = (i ^ *(s32 *)(D_00427334 + 0x9C)) != 0 ? 4 : 8;
        i++;
        func_26EFC8(w, sp, v);
    } while (i < 3);

    v = 0;
    i = 1;
    do {
        i--;
        u = D_00427334 + v;
        v += 0x28;
        func_26EA58(u + 0x10);
    } while (i >= 0);
    return func_24C060();
}
