#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK EftTexSet_Load16(void *, s32);              /* extern */
s32 func_00126460(M2C_UNK);                         /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_003878B4;

void func_001C88E8(s32 arg0) {
    void *temp_s0;
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x168);
    D_003878B4 = temp_v0;
    memset(temp_v0, 0, 0x168);
    M2C_FIELD(D_003878B4, s32 *, 0x120) = 0;
    M2C_FIELD(D_003878B4, s32 *, 0x124) = 0;
    temp_s0 = D_003878B4;
    M2C_FIELD(temp_s0, s32 *, 0) = func_00126460(0x10B);
    EftTexSet_Load16(temp_s0 + 8, func_00126460(0x10C));
    M2C_FIELD(temp_s0, s32 *, 0x114) = func_00126460(0x10D);
    M2C_FIELD(temp_s0, s32 *, 0x118) = func_00126460(0x10A);
    M2C_FIELD(D_003878B4, s32 *, 0x164) = BtlTask_CreateChildList(arg0, 3, 0xA0);
}
