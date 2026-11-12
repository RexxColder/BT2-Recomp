#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
M2C_UNK EftTexSet_Load16(void *, s32);              /* extern */
s32 func_00126460(M2C_UNK);                         /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_003877D0;

void func_00195650(void) {
    s32 temp_v0_2;
    s32 temp_v0_3;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x2E0);
    D_003877D0 = temp_v0;
    memset(temp_v0, 0, 0x2E0);
    temp_s1 = D_003877D0;
    temp_v0_2 = func_00126460(0x31);
    temp_s0 = temp_s1 + 0xA0;
    M2C_FIELD(temp_s1, s32 *, 0xA0) = temp_v0_2;
    EftTexSet_Load16(temp_s1 + 0xA8, temp_v0_2);
    M2C_FIELD(temp_s0, s32 *, 0x118) = func_00126460(0x32);
    M2C_FIELD(temp_s0, s32 *, 0x11C) = func_00126460(0x33);
    temp_v0_3 = func_00126460(0x34);
    M2C_FIELD(temp_s0, s32 *, 0x120) = temp_v0_3;
    EftTexSet_Load16(temp_s1 + 0x1C8, temp_v0_3);
    M2C_FIELD(temp_s0, s32 *, 0x238) = func_00126460(0x35);
    M2C_FIELD(temp_s0, s32 *, 0x23C) = func_00126460(0x36);
}
