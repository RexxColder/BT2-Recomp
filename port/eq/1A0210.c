#include "common.h"

void *BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
void EftTexSet_Load4(void *arg0, s32 arg1);
void EftTexSet_Load16(void *arg0, s32 arg1);
void EftTexSet_Load32(void *arg0, s32 arg1);
s32 func_00126460(s32 arg0);
void *memset(void *, int, unsigned int);
extern u8 *D_00387808;

/* 0x001A0210: allocates the 0x5B8-byte effect block into D_00387808 (zeroed) and fills its texture ids through
 * func_00126460 (0x101, 0x102, 0x55, 0x56, 0x57, 0x11C, 0x11B, 0xB6), loading the texture sets with EftTexSet_Load*.
 * Word 0 of the block gets BtlTask_CreateChildList(arg0, 1, 0x50). */
void func_001A0210(s32 arg0) {
    u8 *obj;
    s32 v;

    D_00387808 = (u8 *)BtlPool_Alloc(BtlPool_GetCurrent(), 0x5B8);
    memset(D_00387808, 0, 0x5B8);
    obj = D_00387808;
    v = func_00126460(0x101);
    *(s32 *)(obj + 0x08) = v;
    EftTexSet_Load32(obj + 0x10, v);
    *(s32 *)(obj + 0x220) = func_00126460(0x102);
    v = func_00126460(0x55);
    *(s32 *)(obj + 0x228) = v;
    EftTexSet_Load16(obj + 0x230, v);
    *(s32 *)(obj + 0x340) = func_00126460(0x56);
    *(s32 *)(obj + 0x344) = func_00126460(0x57);
    v = func_00126460(0x11C);
    *(s32 *)(obj + 0x348) = v;
    EftTexSet_Load4(obj + 0x350, v);
    *(s32 *)(obj + 0x3A0) = func_00126460(0x11B);
    EftTexSet_Load32(D_00387808 + 0x3A8, func_00126460(0xB6));
    *(s32 *)D_00387808 = BtlTask_CreateChildList(arg0, 1, 0x50);
}
