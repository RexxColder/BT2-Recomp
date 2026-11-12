#include "common.h"

s32 BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
s32 EftTexSet_Load16(s32 arg0, s32 arg1);
s32 func_00126460();
s32 memset(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_003420D8 __attribute__((section(".data")));
extern s32 D_003877E8;

void func_0019A9A8(s32 arg0) {
    s32 s0;
    s32 p;
    s32 q;
    s32 a1;

    D_003877E8 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x280);
    memset(D_003877E8, 0, 0x280);
    *(s32 *)(D_003877E8 + 0x238) = 0;
    p = (s32)&D_003420D8;
    a1 = 2;
    q = (s32)&D_003420D8 + 0x24;
    *(s32 *)(D_003877E8 + 0x23C) = 0;
    s0 = D_003877E8;
    do {
        a1 -= 1;
        *(f32 *)(p + 0x0) = 1.0f;
        *(f32 *)(p + 0xC) = 1.0f;
        p += 4;
        *(u8 *)q = 1;
        q += 1;
    } while (a1 >= 0);
    *(s32 *)(s0 + 0x0) = func_00126460(0xF0, a1, 1);
    EftTexSet_Load16(s0 + 0x8, func_00126460(0xF1));
    *(s32 *)(s0 + 0x114) = func_00126460(0xF2);
    *(s32 *)(s0 + 0x118) = func_00126460(0xF3);
    EftTexSet_Load16(s0 + 0x120, func_00126460(0xF4));
    *(s32 *)(s0 + 0x22C) = func_00126460(0xEE);
    *(s32 *)(s0 + 0x230) = func_00126460(0xEF);
    *(s32 *)(D_003877E8 + 0x27C) = BtlTask_CreateChildList(arg0, 3, 0x60);
}
