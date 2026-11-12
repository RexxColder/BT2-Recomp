#include "common.h"

/* 0x001DDB18: p = BtlPool_Alloc(BtlPool_GetCurrent(a0), 0xA0); D_003878D4 = p; memset(p, 0, 0xA0);
   p = D_003878D4; p[0] = func_00126460(0x112); EftTexSet_Load8(p + 8, r); list = BtlTask_CreateChildList(a0, 0x14, 0xD0);
   D_003878D8 = list; return list. */
extern s32 D_003878D4;
extern s32 D_003878D8;
s32 BtlPool_GetCurrent(void);
s32 BtlPool_Alloc(s32 arg0, s32 arg1);
s32 func_00126460(s32 arg0);
void EftTexSet_Load8(s32 arg0, s32 arg1);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);

s32 func_001DDB18(s32 a0) {
    u8 *p;
    s32 r;
    s32 list;

    p = (u8 *)BtlPool_Alloc(BtlPool_GetCurrent(), 0xA0);
    D_003878D4 = (s32)p;
    memset(p, 0, 0xA0);
    p = (u8 *)D_003878D4;
    r = func_00126460(0x112);
    *(s32 *)(p + 0x0) = r;
    EftTexSet_Load8((s32)(p + 0x8), r);
    list = BtlTask_CreateChildList(a0, 0x14, 0xD0);
    D_003878D8 = list;
    return list;
}
