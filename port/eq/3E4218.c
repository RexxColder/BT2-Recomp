#include "common.h"

extern u8 *D_004279CC __attribute__((section(".data")));
extern u8 D_00427CF8[], D_00427D08[], D_00427D18[], D_00427D30[], D_00427D48[], D_00427D60[], D_00427D70[], D_00427D80[];
extern u8 D_00428280[], D_00428680[], D_004286A8[], D_004288A8[], D_004288C0[], D_004288E8[], D_004288F0[];

extern void func_00277E70(u8 *arg0, s32 arg1, s64 arg2);
extern s32 func_0026EBC0(u8 *arg0, u8 *arg1, u8 *arg2);
extern void func_00249FB8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void func_002495A8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
extern void func_00249778(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
extern void func_0026EC48(u8 *arg0, u8 *arg1, u8 *arg2);
extern void func_0026EEC8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
extern void func_0026EFC8(u8 *arg0, u8 *arg1, s32 arg2);
extern void func_0026EC78(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, s32 arg5, s32 arg6, s32 arg7);
extern f32 func_0026F148(u8 *arg0, u8 *arg1);
extern void func_0026EEF8(u8 *arg0, u8 *arg1, f32 farg0);
extern void func_0026EA58(u8 *arg0);
extern void func_0024C060(void);

s32 func_003E4218(void) {
    u8 sp[0xBE0];
    u8 *S;
    u8 *s2;
    s32 i;
    u8 *nm;

    S = D_004279CC;
    func_00277E70(*(u8 **)(S + 0x64), 0, 0x80);
    S = D_004279CC;
    s2 = S + 0x3C;
    func_0026EBC0(s2, D_00427CF8, sp);
    S = D_004279CC;
    func_00249FB8(s2, sp, 0, 0, *(s32 *)(S + 0xC), *(s32 *)(S + 0xD8), 0);
    func_0026EBC0(s2, D_00427D08, sp);
    func_002495A8(s2, sp, D_004279CC + 0xF0, 1);
    func_0026EBC0(s2, D_00427D18, sp);
    func_00249778(s2, sp, D_004279CC + 0xF4, 3);

    /* rect at sp+0x30, copied to sp+0x10 */
    S = D_004279CC;
    *(s32 *)(sp + 0x30) = 0;
    *(s32 *)(sp + 0x38) = 0x200;
    *(s32 *)(sp + 0x34) = *(s32 *)(S + 0xD4) << 5;
    *(s32 *)(sp + 0x40) = 0;
    *(s32 *)(sp + 0x3C) = (*(s32 *)(S + 0xD4) << 5) + 0x20;
    __builtin_memcpy(sp + 0x10, sp + 0x30, 20);
    __builtin_memcpy(sp + 0x30, D_00427D30, 20);
    __builtin_memcpy(sp + 0x50, D_00427D48, 20);
    func_0026EBC0(s2, D_00427D60, sp);
    func_0026EC48(s2, sp, sp + 0x10);
    func_0026EBC0(s2, D_00427D70, sp);
    S = D_004279CC;
    {
        s32 d4 = *(s32 *)(S + 0xD4);
        func_0026EEC8(s2, sp, *(s32 *)(sp + 0x30 + d4 * 4), *(s32 *)(sp + 0x50 + d4 * 4));
    }
    S = D_004279CC;
    if (*(s32 *)(S + 0xD0) & 4) {
        func_0026EFC8(s2, sp, 2);
    } else {
        func_0026EFC8(s2, sp, 1);
    }

    /* 5 menu text names, 255 bytes apart, at sp+0x70 */
    __builtin_memcpy(sp + 0x70, D_00427D80, 1275);
    nm = sp + 0x70;
    for (i = 0; i < 5;) {
        u8 *name = nm;
        nm += 0xFF;
        *(s32 *)(sp + 0x10) = 0;
        *(s32 *)(sp + 0x14) = i << 5;
        *(s32 *)(sp + 0x18) = 0x200;
        *(s32 *)(sp + 0x1C) = (i << 5) + 0x20;
        func_0026EBC0(s2, name, sp);
        func_0026EC48(s2, sp, sp + 0x10);
        S = D_004279CC;
        if (i != *(s32 *)(S + 0xD4)) {
            func_0026EFC8(s2, sp, 4);
            i++;
        } else {
            func_0026EFC8(s2, sp, 8);
            S = D_004279CC;
            if (*(s32 *)(S + 0xD0) & 4) {
                i++;
            } else {
                i++;
                func_0026EBC0(s2, D_00427D60, sp + 0x30);
                {
                    f32 f = func_0026F148(s2, sp);
                    func_0026EEF8(s2, sp + 0x30, f);
                }
            }
        }
    }

    /* 4 icons, 255 bytes apart, at sp+0x570 */
    __builtin_memcpy(sp + 0x570, D_00428280, 1020);
    nm = sp + 0x570;
    for (i = 0; i < 4;) {
        u8 *name = nm;
        nm += 0xFF;
        *(s32 *)(sp + 0x30) = 0;
        *(s32 *)(sp + 0x34) = i << 6;
        *(s32 *)(sp + 0x38) = 0x40;
        *(s32 *)(sp + 0x3C) = (i << 6) + 0x40;
        func_0026EBC0(s2, name, sp);
        S = D_004279CC;
        if ((*(s32 *)(S + 0xD0) & 4) == 0 && *(s32 *)(S + 0xD4) == i) {
            func_0026EC78(s2, sp, S + 0xE0, S + 0xE4, sp + 0x30, 4, 1, 6);
        } else {
            func_0026EC48(s2, sp, sp + 0x30);
        }
        i++;
    }

    /* 2 save/load entries */
    __builtin_memcpy(sp + 0x970, D_00428680, 40);
    __builtin_memcpy(sp + 0x9A0, D_004286A8, 510);
    {
        u8 *rect = sp + 0x970;
        nm = sp + 0x9A0;
        for (i = 0; i < 2;) {
            u8 *name = nm;
            nm += 0xFF;
            func_0026EBC0(s2, name, sp);
            func_0026EC48(s2, sp, rect);
            rect += 0x14;
            S = D_004279CC;
            if (i != *(s32 *)(S + 0xDC)) {
                func_0026EFC8(s2, sp, 4);
                i++;
            } else {
                i++;
                func_0026EFC8(s2, sp, 8);
                func_0026EBC0(s2, D_004288A8, sp + 0xBA0);
                {
                    f32 f = func_0026F148(s2, sp);
                    func_0026EEF8(s2, sp + 0xBA0, f);
                }
            }
        }
    }

    __builtin_memcpy(sp + 0xBB0, D_004288C0, 40);
    __builtin_memcpy(sp + 0xBA0, D_004288E8, 8);
    func_0026EBC0(s2, D_004288A8, sp);
    S = D_004279CC;
    func_0026EC48(s2, sp, sp + 0xBB0 + *(s32 *)(S + 0xDC) * 20);
    func_0026EBC0(s2, D_004288F0, sp);
    S = D_004279CC;
    func_0026EEC8(s2, sp, *(s32 *)(sp + 0xBA0 + *(s32 *)(S + 0xDC) * 4), 0);
    {
        s32 k = 1;
        s32 off = 0;
        do {
            u8 *a0 = D_004279CC + off;
            k--;
            off += 0x28;
            func_0026EA58(a0 + 0x14);
        } while (k >= 0);
    }
    func_0024C060();
    S = D_004279CC;
    *(s32 *)(S + 0x11C) = 1;
    return 1;
}
