#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK EftBoundMgr_AddChar(M2C_UNK);               /* extern */
M2C_UNK EftTexSet_Load32(void *, s32);              /* extern */
s32 func_00126460(M2C_UNK);                         /* extern */
M2C_UNK func_00145A00();                            /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *gEftBound;
extern s32 gEftBoundList;

void func_001458D8(s32 arg0) {
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x220);
    gEftBound = temp_v0;
    memset(temp_v0, 0, 0x220);
    M2C_FIELD(gEftBound, s32 *, 0xC) = func_00126460(0x27);
    M2C_FIELD(gEftBound, s32 *, 0x218) = func_00126460(0x5E);
    M2C_FIELD(gEftBound, s32 *, 0x21C) = func_00126460(0x5F);
    EftTexSet_Load32(gEftBound + 0x10, M2C_FIELD(gEftBound, s32 *, 0xC));
    func_00145A00();
    gEftBoundList = BtlTask_CreateChildList(arg0, 2, 0x1050);
    EftBoundMgr_AddChar(0);
    EftBoundMgr_AddChar(1);
}
