#include "common.h"

extern u8 *D_00421380 __attribute__((section(".data")));
extern u8 D_004213C0[] __attribute__((section(".data")));
extern u8 D_004213D8[] __attribute__((section(".data")));
extern u8 D_00421400 __attribute__((section(".data")));
extern u8 D_00421418[] __attribute__((section(".data")));
extern u8 D_00421430 __attribute__((section(".data")));
extern u8 D_00421448[] __attribute__((section(".data")));
extern u8 D_00421460 __attribute__((section(".data")));
extern u8 D_00421470[] __attribute__((section(".data")));
extern u8 D_004216F0 __attribute__((section(".data")));
extern u8 D_00421700 __attribute__((section(".data")));
extern u8 D_00421710 __attribute__((section(".data")));
extern u8 D_00421728 __attribute__((section(".data")));
extern u8 D_00421740 __attribute__((section(".data")));
extern u8 D_00421750[] __attribute__((section(".data")));
extern u8 D_00421768[] __attribute__((section(".data")));
extern u8 D_00421770 __attribute__((section(".data")));
extern u8 D_00421778 __attribute__((section(".data")));

void func_26EBC0(u8 *arg0, u8 *arg1, u8 *arg2);
void func_26EC18(u8 *arg0, u8 *arg1, s32 arg2);
void func_26EC48(u8 *arg0, u8 *arg1, u8 *arg2);
void func_26EC78(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, s32 arg5, s32 arg6, s32 arg7);
void func_26ED60(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, f32 arg5, f32 arg6);
void func_2495A8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_249778(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_2498D8(u8 *arg0, u8 *arg1, s32 arg2);
void func_249FB8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, s32 arg6);
void func_26EA58(u8 *arg0);
void func_24C060(void);

/* 0x003B37A8: menu draw. G = D_00421380; sprite blocks are set up on s1 = G+0x38 (then G+0x60, G+0x10) with a frame
 * record at sp+0 and sub-records at sp+0x10 (0x14 bytes) / sp+0x30 (0x28 bytes). */
void func_003B37A8(void) {
    u8 sp[0x340];
    u8 *s1;
    s32 a3, v, s2, j;

    __builtin_memcpy(sp + 0x10, D_004213C0, 0x14);
    s1 = D_00421380 + 0x38;
    __builtin_memcpy(sp + 0x30, D_004213D8, 0x28);
    func_26EBC0(s1, &D_00421400, sp);
    func_26EC18(s1, sp, *(s32 *)(D_00421380 + 0xE8));
    a3 = *(s32 *)(D_00421380 + 0xE8);
    if (a3 == 3) {
        func_26EC78(s1, sp, D_00421380 + 0x100, D_00421380 + 0x104, sp + 0x10, *(s32 *)(sp + 0x3C), 1, 7);
    } else {
        func_26EC78(s1, sp, D_00421380 + 0x100, D_00421380 + 0x104, sp + 0x10, *(s32 *)(sp + 0x30 + a3 * 4), 1, 6);
    }

    __builtin_memcpy(sp + 0x10, D_00421418, 0x14);
    a3 = *(s32 *)(D_00421380 + 0xE8);
    v = (a3 < 0 ? a3 + 3 : a3) >> 2;
    *(s32 *)(sp + 0x14) = (a3 - v * 4) << 6;
    *(s32 *)(sp + 0x1C) = ((a3 - v * 4) << 6) + 0x40;
    func_26EBC0(s1, &D_00421430, sp);
    a3 = *(s32 *)(D_00421380 + 0xE8);
    func_26EC18(s1, sp, (a3 < 0 ? a3 + 3 : a3) >> 2);
    func_26EC48(s1, sp, sp + 0x10);

    __builtin_memcpy(sp + 0x30, D_00421448, 0x14);
    func_26EBC0(s1, &D_00421460, sp);
    func_26EC48(s1, sp, sp + 0x30);

    __builtin_memcpy(sp + 0x60, D_00421470, 0x280);
    __builtin_memcpy(sp + 0x10, D_00421418, 0x14);
    s2 = 0;
    do {
        u8 *a1 = sp + 0x60 + s2 * 0x80;
        s32 w = *(s32 *)(D_00421380 + 0xF0) + s2;
        s2++;
        a3 = w % 10;
        v = (a3 < 0 ? a3 + 3 : a3) >> 2;
        *(s32 *)(sp + 0x14) = (a3 - v * 4) << 6;
        *(s32 *)(sp + 0x1C) = ((a3 - v * 4) << 6) + 0x40;
        func_26EBC0(s1, a1, sp);
        func_26EC18(s1, sp, v);
        func_26EC48(s1, sp, sp + 0x10);
    } while (s2 < 5);

    s1 = D_00421380 + 0x60;
    func_26EBC0(s1, &D_004216F0, sp);
    func_2495A8(s1, sp, D_00421380 + 0x110, 1);
    func_26EBC0(s1, &D_00421700, sp);
    if (*(s32 *)(D_00421380 + 0xF4) != 0) {
        func_2498D8(s1, sp, 3);
    } else {
        func_249778(s1, sp, D_00421380 + 0x118, 3);
    }
    func_26EBC0(s1, &D_00421710, sp);
    func_2495A8(s1, sp, D_00421380 + 0x114, 5);
    func_26EBC0(s1, &D_00421728, sp);
    if (*(s32 *)(D_00421380 + 0xF4) == 1) {
        func_249778(s1, sp, D_00421380 + 0x11C, 7);
    } else {
        func_2498D8(s1, sp, 7);
    }
    func_26EBC0(s1, &D_00421740, sp);
    func_249FB8(s1, sp, 0, 0, *(u8 **)(D_00421380 + 8), *(s32 *)(D_00421380 + 0xEC), 0);

    __builtin_memcpy(sp + 0x30, D_00421750, 0x14);
    __builtin_memcpy(sp + 0x2E0, D_00421768, 8);
    s1 = D_00421380 + 0x10;
    for (s2 = 0; s2 < 2; s2++) {
        func_26EBC0(s1, s2 == 0 ? &D_00421770 : &D_00421778, sp);
        func_26ED60(s1, sp, sp + 0x30, D_00421380 + s2 * 4 + 0x108, 0, *(f32 *)(sp + 0x2E0 + s2 * 4), 0.0f);
    }

    for (j = 0; j < 3; j++) {
        if (j == 2) {
            func_24C060();
        }
        func_26EA58(D_00421380 + j * 0x28 + 0x10);
    }
}
