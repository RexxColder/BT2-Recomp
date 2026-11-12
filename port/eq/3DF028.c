#include "common.h"

extern u8 *D_00427330 __attribute__((section(".data")));
extern u8 D_00427520[] __attribute__((section(".data")));
extern u8 D_00427530[] __attribute__((section(".data")));
extern u8 D_00427540[] __attribute__((section(".data")));
extern u8 D_00427550[] __attribute__((section(".data")));
extern u8 D_00427560[] __attribute__((section(".data")));
extern u8 D_00427570[] __attribute__((section(".data")));
extern u8 D_00427580[] __attribute__((section(".data")));
extern u8 D_00427590[] __attribute__((section(".data")));

s32 func_00277E70(void *a0, s32 a1, s64 a2);
void func_0026EBC0(u8 *a0, u8 *a1, u8 *a2);
void func_0026EFC8(u8 *a0, u8 *a1, s32 a2);
void func_0026EC48(u8 *a0, u8 *a1, u8 *a2);
f32 func_0026F148(u8 *a0, u8 *a1);
s32 func_002A0EA8(u8 *a0);
void func_003DEA48(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, s32 t2, s32 t3, s32 stk0);
void func_0026EA58(u8 *a0);
void BattleSetup_Finish(void);
void func_002495A8(u8 *a0, u8 *a1, u8 *a2, s32 a3);
void func_00249778(u8 *a0, u8 *a1, u8 *a2, s32 a3);
void func_00249FB8(u8 *a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, s32 t2);

/* 0x003DF028: battle setup step on the object at D_00427330. sp+0x10 is the parameter block
   and sp+0x20..0x2C the (x, y, w, h) style rectangle words used by func_26EC48. */
void func_003DF028(void) {
    u8 sp[0x40];
    u8 *G;
    u8 *s1;
    u8 *s3;
    s32 x;
    s32 dc;
    f32 r;

    G = D_00427330;
    func_00277E70(*(u8 **)(G + 0x80), 0, 0x80);

    G = D_00427330;
    s1 = G + 0x14;
    func_0026EBC0(s1, D_00427520, sp + 0x10);

    G = D_00427330;
    if (*(s32 *)(G + 0xF8) > 0) {
        func_0026EFC8(s1, sp + 0x10, 4);
    } else {
        func_0026EFC8(s1, sp + 0x10, 8);
    }

    *(s32 *)(sp + 0x20) = 0x20;
    *(s32 *)(sp + 0x24) = 0;
    *(s32 *)(sp + 0x28) = 0x40;
    *(s32 *)(sp + 0x2C) = 0x20;
    func_0026EBC0(s1, D_00427530, sp + 0x10);
    s3 = sp + 0x20;
    func_0026EC48(s1, sp + 0x10, s3);

    G = D_00427330;
    if (*(s32 *)(G + 0xF8) < *(s32 *)(G + 0x104) - 10) {
        func_0026EFC8(s1, sp + 0x10, 4);
    } else {
        func_0026EFC8(s1, sp + 0x10, 8);
    }
    func_0026EBC0(s1, D_00427540, sp + 0x10);

    r = func_0026F148(s1, sp + 0x10);
    if (r < 0.01f) {
        G = D_00427330;
        *(s32 *)(G + 0xDC) |= 8;
        G = D_00427330;
        *(s32 *)(G + 0x104) = func_002A0EA8(*(u8 **)(G + 0x10) + (*(s32 *)(*(u8 **)(G + 0x10) + 4 * *(s32 *)(G + 0xE4) + 0x414) & ~3));
        G = D_00427330;
        *(s32 *)(G + 0xF8) = 0;
        *(s32 *)(G + 0xFC) = 0;
    }

    G = D_00427330;
    dc = *(s32 *)(G + 0xDC);
    /* x = E4 when dc & 8 is set, else E8 */
    x = (dc & 8) != 0 ? *(s32 *)(G + 0xE4) : *(s32 *)(G + 0xE8);
    *(s32 *)(sp + 0x20) = ((x % 2) << 8);
    *(s32 *)(sp + 0x24) = ((x / 2) << 5);
    *(s32 *)(sp + 0x28) = *(s32 *)(sp + 0x20) + 0x100;
    *(s32 *)(sp + 0x2C) = *(s32 *)(sp + 0x24) + 0x20;
    func_0026EC48(s1, sp + 0x10, s3);

    G = D_00427330;
    dc = *(s32 *)(G + 0xDC);
    x = (dc & 8) != 0 ? *(s32 *)(G + 0xE4) : *(s32 *)(G + 0xE8);
    *(s32 *)(sp + 0x20) = ((x % 4) << 5);
    *(s32 *)(sp + 0x24) = ((x / 4) << 5);
    *(s32 *)(sp + 0x28) = *(s32 *)(sp + 0x20) + 0x20;
    *(s32 *)(sp + 0x2C) = *(s32 *)(sp + 0x24) + 0x20;
    func_0026EBC0(s1, D_00427550, sp + 0x10);
    func_0026EC48(s1, sp + 0x10, s3);
    func_0026EBC0(s1, D_00427560, sp + 0x10);

    G = D_00427330;
    dc = *(s32 *)(G + 0xDC);
    x = (dc & 8) != 0 ? *(s32 *)(G + 0xE4) : *(s32 *)(G + 0xE8);
    /* 9th argument: 10 in the dc & 8 case, 0 otherwise */
    func_003DEA48(s1, sp + 0x10, 0, -2, *(u8 **)(G + 0x10), x + 0x105, 0,
                  *(s32 *)(G + 0xFC), (dc & 8) != 0 ? 10 : 0);
    func_0026EA58(s1);
    BattleSetup_Finish();

    G = D_00427330;
    s1 = G + 0x3C;
    func_0026EBC0(s1, D_00427570, sp + 0x10);
    G = D_00427330;
    func_002495A8(s1, sp + 0x10, G + 0xF0, 1);
    func_0026EBC0(s1, D_00427580, sp + 0x10);
    G = D_00427330;
    func_00249778(s1, sp + 0x10, G + 0xF4, 3);
    func_0026EBC0(s1, D_00427590, sp + 0x10);
    G = D_00427330;
    func_00249FB8(s1, sp + 0x10, 0, 0, *(u8 **)(G + 0x8), *(s32 *)(G + 0xE0), 1);
    func_0026EA58(s1);
    BattleSetup_Finish();
}
