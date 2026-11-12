#include "common.h"

/* 0x001E7670: p = BtlPool_Alloc(BtlPool_GetCurrent(a0), 0x1298); D_003878F4 = p; memset(p, 0, 0x1298);
   func_00126460(1); EftTexSet_Load32(p + 8, r); list = BtlTask_CreateChildList(a0, 2, 0xA0);
   *(s32 *)D_003878F4 = list; tail func_001E8B20(). */
extern u8 D_003878F4[];
s32 BtlPool_GetCurrent(void);
s32 BtlPool_Alloc(s32 arg0, s32 arg1);
s32 func_00126460(s32 arg0);
s32 EftTexSet_Load32(s32 arg0, s32 arg1);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
s32 func_001E8B20(void);

s32 func_001E7670(s32 a0) {
    u8 *p;
    s32 r;
    s32 list;

    p = (u8 *)BtlPool_Alloc(BtlPool_GetCurrent(), 0x1298);
    *(u8 **)D_003878F4 = p;
    memset(p, 0, 0x1298);
    r = func_00126460(1);
    EftTexSet_Load32((s32)(*(u8 **)D_003878F4 + 8), r);
    list = BtlTask_CreateChildList(a0, 2, 0xA0);
    *(s32 *)*(u8 **)D_003878F4 = list;
    return func_001E8B20();
}
