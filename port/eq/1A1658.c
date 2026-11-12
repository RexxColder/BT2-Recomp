#include "common.h"

void *BtlPool_GetCurrent(void *arg0);
void *BtlPool_Alloc(void *arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, s32 arg2);
void *func_00126460(s32 arg0);
void EftTexSet_Load16(void *arg0, void *arg1);
void *BtlTask_CreateChildList(void *arg0, s32 arg1, s32 arg2);
extern u8 *D_00387814;

/* 0x001A1658(a0): pool = BtlPool_GetCurrent(a0); D_00387814 = BtlPool_Alloc(pool, 0x128), cleared; +8 = func_00126460(0x55),
 * EftTexSet_Load16(block + 0x10, that); +0x120 = func_00126460(0x56); +0x124 = func_00126460(0x57);
 * D_00387814 word 0 = BtlTask_CreateChildList(a0, 2, 0x30). */
void func_001A1658(void *arg0) {
    void *pool = BtlPool_GetCurrent(arg0);
    void *blk = BtlPool_Alloc(pool, 0x128);
    u8 *s1;
    void *v;
    void *v56;

    D_00387814 = blk;
    memset(blk, 0, 0x128);
    s1 = D_00387814;
    v = func_00126460(0x55);
    *(void **)(s1 + 8) = v;
    EftTexSet_Load16(s1 + 0x10, v);
    v56 = func_00126460(0x56);
    *(void **)(s1 + 8 + 0x118) = v56;
    *(void **)(s1 + 8 + 0x11C) = func_00126460(0x57);
    *(void **)D_00387814 = BtlTask_CreateChildList(arg0, 2, 0x30);
}
