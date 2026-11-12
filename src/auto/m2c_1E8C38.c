#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK EftTexSet_Load16(void *, s32);              /* extern */
s32 func_00126460(M2C_UNK);                         /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_003878F8;

void func_001E8C38(s32 arg0) {
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x2CE0);
    D_003878F8 = temp_v0;
    memset(temp_v0, 0, 0x2CE0);
    M2C_FIELD(D_003878F8, s32 *, 0x2CD0) = func_00126460(0x26);
    EftTexSet_Load16(D_003878F8 + 0x2BC8, M2C_FIELD(D_003878F8, s32 *, 0x2CD0));
    M2C_FIELD(D_003878F8, s32 *, 0x2BC4) = BtlTask_CreateChildList(arg0, 0x96, 0x190);
}
