#include "common.h"

extern u8 *D_0042BB84 __attribute__((section(".data")));
extern u8 D_0042F508[] __attribute__((section(".data")));
extern u8 D_0042F518[] __attribute__((section(".data")));
extern u8 D_0042F528[] __attribute__((section(".data")));
extern u8 D_0042F538[] __attribute__((section(".data")));
extern u8 D_0042F548[] __attribute__((section(".data")));
extern u8 D_0042F560[] __attribute__((section(".data")));
extern u8 D_0042F578[] __attribute__((section(".data")));
extern u8 D_0042F590[] __attribute__((section(".data")));
extern u8 D_0042F5A8[] __attribute__((section(".data")));
extern u8 D_0042F5C0[] __attribute__((section(".data")));
extern u8 D_0042F5D0[] __attribute__((section(".data")));
extern u8 D_0042F9D0[] __attribute__((section(".data")));
extern u8 D_0042FA10[] __attribute__((section(".data")));
extern u8 D_0042FA20[] __attribute__((section(".data")));
extern u8 D_0042FA38[] __attribute__((section(".data")));

void func_00277E70(u8 *arg0, s32 arg1, s64 arg2);
void func_0026EBC0(u8 *a0, u8 *a1, u8 *a2);
void func_00249FB8(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *a4, s32 a5, s32 a6);
void func_002495A8(u8 *a0, u8 *a1, u8 *a2, s32 a3);
void func_00249778(u8 *a0, u8 *a1, u8 *a2, s32 a3);
void func_0026EEC8(u8 *a0, u8 *a1, s32 a2, s32 a3);
void func_0026EFC8(u8 *a0, u8 *a1, s32 a2);
void func_0026EEF8(u8 *a0, u8 *a1, f32 f);
void func_0026EF88(u8 *a0, u8 *a1, f32 f);
f32 func_0026F148(u8 *a0, u8 *a1);
void func_0026EC48(u8 *a0, u8 *a1, u8 *a2);
void func_0026EC78(u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, s32 t1, s32 t2, s32 t3);
void func_0024C060(void);
void func_0026EA58(u8 *a0);

void func_0041AE58(void) {
    u8 sp[0x7E0];
    u8 *s2;
    u8 *obj;
    s32 i;
    s32 idx;
    s32 y;
    f32 f;

    obj = D_0042BB84;
    func_00277E70(*(u8 **)(obj + 0x60), 0, 0x80);
    obj = D_0042BB84;
    s2 = obj + 0x38;
    func_0026EBC0(s2, D_0042F508, sp);
    obj = D_0042BB84;
    func_00249FB8(s2, sp, 0, 0, *(u8 **)(obj + 0xC), *(s32 *)(obj + 0xF8), 0);
    func_0026EBC0(s2, D_0042F518, sp);
    func_002495A8(s2, sp, D_0042BB84 + 0x108, 1);
    func_0026EBC0(s2, D_0042F528, sp);
    func_00249778(s2, sp, D_0042BB84 + 0x10C, 3);

    __builtin_memcpy(sp + 0x10, D_0042F538, 16);
    func_0026EBC0(s2, D_0042F548, sp);
    idx = *(s32 *)(D_0042BB84 + 0xF4);
    func_0026EEC8(s2, sp, *(s32 *)(sp + 0x10 + idx * 4), idx * 40);
    if (*(u32 *)(D_0042BB84 + 0xF0) & 4) {
        func_0026EFC8(s2, sp, 2);
        func_0026EEF8(s2, sp, 0x1.b33332p-1f);   /* 0x3F599999 */
    } else {
        func_0026EFC8(s2, sp, 1);
    }

    y = *(s32 *)(D_0042BB84 + 0xF4) << 5;
    *(s32 *)(sp + 0x28) = 0x200;
    *(s32 *)(sp + 0x20) = 0;
    *(s32 *)(sp + 0x24) = y;
    *(s32 *)(sp + 0x2C) = y + 0x20;
    func_0026EBC0(s2, D_0042F560, sp);
    func_0026EC48(s2, sp, sp + 0x20);

    if (!(*(u32 *)(D_0042BB84 + 0xF0) & 4)) {
        __builtin_memcpy(sp + 0x40, D_0042F578, 20);
        func_0026EBC0(s2, D_0042F590, sp);
        obj = D_0042BB84;
        func_0026EC78(s2, sp, obj + 0x118, obj + 0x12C, sp + 0x40, 1, 6, 2);

        __builtin_memcpy(sp + 0x60, D_0042F5A8, 20);
        func_0026EBC0(s2, D_0042F5C0, sp);
        obj = D_0042BB84;
        func_0026EC78(s2, sp, obj + 0x11C, obj + 0x130, sp + 0x60, 6, 1, 4);
    }

    __builtin_memcpy(sp + 0x80, D_0042F5D0, 0x3FC);
    {
        u8 *name = sp + 0x80;
        for (i = 0, y = 0; ; ) {
            u8 *cur = name;
            *(s32 *)(sp + 0x10) = 0;
            *(s32 *)(sp + 0x14) = y;
            *(s32 *)(sp + 0x18) = 0x200;
            *(s32 *)(sp + 0x1C) = y + 0x20;
            name += 0xFF;
            func_0026EBC0(s2, cur, sp);
            func_0026EC48(s2, sp, sp + 0x10);
            obj = D_0042BB84;
            if (i == *(s32 *)(obj + 0xF4)) {
                func_0026EFC8(s2, sp, 8);
                if (!(*(u32 *)(obj + 0xF0) & 4)) {
                    i++;
                    func_0026EBC0(s2, D_0042F548, sp + 0x30);
                    f = func_0026F148(s2, sp);
                    func_0026EEF8(s2, sp + 0x30, f);
                    goto next;
                }
            } else {
                if (i == 1) {
                    if (*(u32 *)(obj + 0xF0) & 8) {
                        func_0026EF88(s2, sp, 0x1.99999cp-2f);   /* 0x3ECCCCCC */
                    } else {
                        func_0026EF88(s2, sp, 1.0f);
                    }
                }
                func_0026EFC8(s2, sp, 4);
            }
            i++;
        next:
            y = i << 5;
            if (!(i < 4)) break;
        }
    }

    __builtin_memcpy(sp + 0x480, D_0042F9D0, 0x3C);
    func_0026EBC0(s2, D_0042FA10, sp);
    obj = D_0042BB84;
    func_0026EC48(s2, sp, sp + 0x480 + *(s32 *)(obj + 0xFC) * 20);

    *(s32 *)(sp + 0x3C) = 0x20;
    *(s32 *)(sp + 0x38) = 0x40;
    *(s32 *)(sp + 0x30) = 0x20;
    func_0026EBC0(s2, D_0042FA20, sp);
    *(s32 *)(sp + 0x34) = 0;
    func_0026EC48(s2, sp, sp + 0x30);

    obj = D_0042BB84;
    s2 = obj + 0x10;
    __builtin_memcpy(sp + 0x4C0, D_0042F5A8, 20);
    __builtin_memcpy(sp + 0x4E0, D_0042FA38, 0x2FD);
    {
        u8 *name = sp + 0x4E0;
        for (i = 0; ; ) {
            u8 *cur = name;
            name += 0xFF;
            func_0026EBC0(s2, cur, sp);
            obj = D_0042BB84;
            func_0026EC78(s2, sp, obj + i * 4 + 0x120, obj + i * 4 + 0x134, sp + 0x4C0, 6, 1, 4);
            i++;
            if (!(i < 3)) break;
        }
    }

    func_0024C060();
    {
        s32 off = 0;
        s32 n = 1;
        do {
            n--;
            func_0026EA58(D_0042BB84 + off + 0x10);
            off += 0x28;
        } while (n >= 0);
    }
}
