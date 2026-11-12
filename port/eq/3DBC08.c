#include "common.h"

extern u8 *D_004263EC __attribute__((section(".data")));
extern u8 D_00426ED0[] __attribute__((section(".data")));
extern u8 D_00426EE0[] __attribute__((section(".data")));
extern u8 D_00426EF0[] __attribute__((section(".data")));
extern u8 D_004271F0[] __attribute__((section(".data")));
extern u8 D_00427200[] __attribute__((section(".data")));
extern u8 D_00427210[] __attribute__((section(".data")));
extern u8 D_00427220[] __attribute__((section(".data")));
extern u8 D_00427230[] __attribute__((section(".data")));

s32 func_00277E70(void *a0, s32 a1, s64 a2);
void func_0026EBC0(u8 *a0, u8 *a1, u8 *a2);
void func_00249778(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_00249FB8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, s32 arg6);
void func_0026EC48(u8 *a0, u8 *a1, u8 *a2);
void func_0026EFC8(u8 *a0, u8 *a1, s32 a2);
void func_0026EEC8(u8 *a0, u8 *a1, s32 a2, s32 a3);
void func_0026EA58(u8 *a0);
void func_0024C060(void);

/* byte copy (no libc) */
static void blob_copy(u8 *d, u8 *s, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

/* 0x003DBC08: frame-local parameter block at sp (sp+0x10..0x1C), data copy at sp+0x30 and sp+0x330.
   G = D_004263EC is the game object. */
void func_003DBC08(void) {
    u8 sp[0x340];
    u8 *G;
    u8 *s3;
    u8 *d;
    s32 i;
    s32 v;

    G = D_004263EC;
    func_00277E70(*(u8 **)(G + 0x38), 0, 0x80);

    G = D_004263EC;
    s3 = G + 0x10;
    func_0026EBC0(s3, D_00426ED0, sp);

    G = D_004263EC;
    func_00249778(s3, sp, G + 0x7C, 1);
    func_0026EBC0(s3, D_00426EE0, sp);

    G = D_004263EC;
    func_00249FB8(s3, sp, 0, 0, *(u8 **)(G + 0x8), *(s32 *)(G + 0x68), 1);

    blob_copy(sp + 0x30, D_00426EF0, 0x2FD);

    d = sp + 0x30;
    i = 0;
    do {
        G = D_004263EC;
        if (i < *(s32 *)(G + 0x6C)) {
            *(s32 *)(sp + 0x10) = 0;
            *(s32 *)(sp + 0x14) = i * 32;
            *(s32 *)(sp + 0x18) = 0x200;
            *(s32 *)(sp + 0x1C) = i * 32 + 0x20;
        } else {
            *(s32 *)(sp + 0x14) = 0x60;
            *(s32 *)(sp + 0x1C) = 0x80;
            *(s32 *)(sp + 0x10) = 0;
            *(s32 *)(sp + 0x18) = 0x200;
        }
        func_0026EBC0(s3, d, sp);
        d += 0xFF;
        func_0026EC48(s3, sp, sp + 0x10);

        G = D_004263EC;
        if (i != *(s32 *)(G + 0x64)) {
            func_0026EFC8(s3, sp, 4);
        } else {
            func_0026EFC8(s3, sp, 8);
        }
        i++;
    } while (i < 3);

    blob_copy(sp + 0x330, D_004271F0, 12);
    func_0026EBC0(s3, D_00427200, sp);

    G = D_004263EC;
    v = *(s32 *)(G + 0x64);
    func_0026EEC8(s3, sp, *(s32 *)(sp + 0x330 + 4 * v), 54 * v);

    G = D_004263EC;
    v = *(s32 *)(G + 0x64);
    *(s32 *)(sp + 0x10) = 0;
    *(s32 *)(sp + 0x18) = 0x200;
    *(s32 *)(sp + 0x14) = v * 32;
    *(s32 *)(sp + 0x1C) = v * 32 + 0x20;
    func_0026EBC0(s3, D_00427210, sp);
    func_0026EC48(s3, sp, sp + 0x10);

    *(s32 *)(sp + 0x1C) = 0x40;
    *(s32 *)(sp + 0x14) = 0x20;
    *(s32 *)(sp + 0x18) = 0x200;
    *(s32 *)(sp + 0x10) = 0;
    func_0026EBC0(s3, D_00427220, sp);
    func_0026EC48(s3, sp, sp + 0x10);

    G = D_004263EC;
    if (*(s32 *)(G + 0x78) != 0 || *(s32 *)(G + 0x64) != 0) {
        func_0026EFC8(s3, sp, 8);
    } else {
        func_0026EFC8(s3, sp, 4);
    }

    G = D_004263EC;
    if ((*(s32 *)(G + 0x60) & 4) != 0) {
        *(s32 *)(sp + 0x14) = 0x40;
        *(s32 *)(sp + 0x1C) = 0x60;
        *(s32 *)(sp + 0x18) = 0x200;
    } else {
        *(s32 *)(sp + 0x1C) = 0x20;
        *(s32 *)(sp + 0x18) = 0x200;
        *(s32 *)(sp + 0x14) = 0;
    }
    *(s32 *)(sp + 0x10) = 0;
    func_0026EBC0(s3, D_00427230, sp);
    func_0026EC48(s3, sp, sp + 0x10);

    G = D_004263EC;
    func_0026EA58(G + 0x10);
    func_0024C060();
}
