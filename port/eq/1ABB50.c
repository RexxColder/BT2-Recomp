#include "common.h"

extern u8 *D_00387848;
extern u8 *D_003876A0;

u8 *BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void EftTexSet_Load16(u8 *arg0, s32 arg1);
void EftTexSet_Load32(u8 *arg0, s32 arg1);
void EftTexSet_Load8(u8 *arg0, s32 arg1);
s32 func_00126460(s32 arg0);
void memset(u8 *arg0, s32 arg1, s32 arg2);

void func_001ABB50(s32 arg0) {
    u8 *base;
    u8 *s4p;
    u8 *pa;
    u8 *pb;
    u8 *pc;
    u8 *pd;
    u8 *pe;
    s32 s1;
    s32 off;
    s32 v;

    D_00387848 = BtlPool_Alloc(BtlPool_GetCurrent(), 0xE88);
    memset(D_00387848, 0, 0xE88);
    base = D_00387848;
    s4p = base + 8;

    v = func_00126460(0xB4);
    *(s32 *)(s4p + 0) = v;
    v = func_00126460(0xB5);
    *(s32 *)(s4p + 8) = v;
    EftTexSet_Load16(base + 0x18, v);
    v = func_00126460(0xB6);
    *(s32 *)(s4p + 0x128) = v;
    EftTexSet_Load16(base + 0x138, v);
    *(s32 *)(s4p + 0x368) = func_00126460(0xBA);
    *(s32 *)(s4p + 0x36C) = func_00126460(0xBB);
    v = func_00126460(0xC7);
    *(s32 *)(s4p + 0x248) = v;
    EftTexSet_Load16(base + 0x258, v);
    *(s32 *)(s4p + 0x360) = func_00126460(0xC8);
    *(s32 *)(s4p + 0x364) = func_00126460(0xC9);

    /* loop 1: 3 iterations */
    pa = base + 0x378;
    pb = base + 0x380;
    pc = base + 0x540;
    pd = base + 0x54C;
    s1 = 0;
    do {
        v = func_00126460(s1 + 0xDE);
        *(s32 *)pa = v;
        pa += 0x98;
        EftTexSet_Load8(pb, v);
        pb += 0x98;
        *(s32 *)pc = func_00126460(s1 + 0xE1);
        pc += 4;
        *(s32 *)pd = func_00126460(s1 + 0xE4);
        pd += 4;
        s1 += 1;
    } while (s1 < 3);

    /* loop 2: 3 iterations, byte offset 0x550 + 4*i */
    s1 = 0;
    off = 0x550;
    do {
        *(s32 *)(s4p + off) = func_00126460(s1 + 0xE7);
        v = func_00126460(s1 + 0xEA);
        s1 += 1;
        *(s32 *)(s4p + 0xC + off) = v;
        off += 4;
    } while (s1 < 3);

    /* loop 3: 4 iterations */
    s1 = 0;
    pe = base + 0x9E0;
    pc = s4p + 0x570;
    pb = s4p + 0x568;
    do {
        v = func_00126460(s1 + 0xCA);
        *(s32 *)pb = v;
        pb += 0x118;
        EftTexSet_Load16(pc, v);
        pc += 0x118;
        *(s32 *)(pe - 0x10) = func_00126460(s1 + 0xCE);
        v = func_00126460(s1 + 0xD2);
        s1 += 1;
        *(s32 *)pe = v;
        pe += 4;
    } while (s1 < 4);

    /* loop 4: 4 iterations */
    s1 = 0;
    pe = base + 0xA00;
    do {
        *(s32 *)(pe - 0x10) = func_00126460(s1 + 0xD6);
        v = func_00126460(s1 + 0xDA);
        s1 += 1;
        *(s32 *)pe = v;
        pe += 4;
    } while (s1 < 4);

    v = func_00126460(0xBF);
    *(s32 *)(s4p + 0xA28) = v;
    EftTexSet_Load32(s4p + 0xA30, v);

    /* loop 5: 7 iterations */
    s1 = 0;
    pe = base + 0xA10;
    do {
        v = func_00126460(s1 + 0xC0);
        s1 += 1;
        *(s32 *)pe = v;
        pe += 4;
    } while (s1 < 7);

    v = func_00126460(0xB7);
    *(s32 *)(s4p + 0xC40) = v;
    EftTexSet_Load16(s4p + 0xC48, v);
    *(s32 *)(s4p + 0xD58) = func_00126460(0xB8);
    *(s32 *)(s4p + 0xD5C) = func_00126460(0xB9);
    v = func_00126460(0xBC);
    *(s32 *)(s4p + 0xD60) = v;
    EftTexSet_Load16(s4p + 0xD68, v);
    *(s32 *)(s4p + 0xE78) = func_00126460(0xBD);
    *(s32 *)(s4p + 0xE7C) = func_00126460(0xBE);

    v = BtlTask_CreateChildList(arg0,
                                (*(s64 *)(D_003876A0 + 0x4D8) & 2) ? 0x14 : 0x1E,
                                0xF0, 0x1E);
    *(s32 *)D_00387848 = v;
}
