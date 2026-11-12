#include "common.h"

s32 BtlPool_GetCurrent(s32 arg0);
u8 *BtlPool_Alloc(s32 arg0, s32 arg1);
void memset(void *arg0, s32 arg1, s32 arg2);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
void EftTexSet_Load16(s32 arg0, s32 arg1);
s32 func_00126460(s32 arg0);
extern u8 *D_00387850;
extern s32 D_00387854;

void func_001ADE08(s32 arg0) {
    u8 *p;
    u8 *s1;
    u8 *s0;
    s32 i;
    s32 off;
    s32 v;

    i = 0;
    off = 0x350;
    p = BtlPool_Alloc(BtlPool_GetCurrent(arg0), 0x5B0);
    D_00387850 = p;
    memset(p, 0, 0x5B0);
    s1 = D_00387850;
    *(s32 *)(s1 + 0) = func_00126460(0xA4);
    s0 = s1;
    do {
        v = func_00126460(i + 0xA5);
        *(s32 *)(s0 + 8) = v;
        EftTexSet_Load16((s32)(s0 + 0x10), v);
        s0 += 0x118;
        *(s32 *)(s1 + off) = func_00126460(i + 0xA8);
        v = i + 0xAB;
        i += 1;
        *(s32 *)(s1 + 0xC + off) = func_00126460(v);
        off += 4;
    } while (i < 3);
    v = func_00126460(0xAE);
    *(s32 *)(s1 + 0x368) = v;
    EftTexSet_Load16((s32)(s1 + 0x370), v);
    *(s32 *)(s1 + 0x480) = func_00126460(0xAF);
    *(s32 *)(s1 + 0x484) = func_00126460(0xB0);
    v = func_00126460(0xB1);
    *(s32 *)(s1 + 0x488) = v;
    EftTexSet_Load16((s32)(s1 + 0x490), v);
    *(s32 *)(s1 + 0x5A0) = func_00126460(0xB2);
    *(s32 *)(s1 + 0x5A4) = func_00126460(0xB3);
    D_00387854 = BtlTask_CreateChildList(arg0, 0xA, 0x70);
}
