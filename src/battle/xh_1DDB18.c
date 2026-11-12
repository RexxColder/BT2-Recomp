#include "m2c_macros.h"

s32 *BtlPool_Alloc(s32, M2C_UNK);                   /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK EftTexSet_Load8(s32 *, s32);                /* extern */
s32 func_00126460(M2C_UNK);                         /* extern */
M2C_UNK memset(s32 *, M2C_UNK, M2C_UNK);            /* extern */
extern s32 *D_003878D4;
extern s32 D_003878D8;

// Allocates a 0xA0-byte object into D_003878D4, loads texture 0x112 into it, creates child task list into D_003878D8.
void func_001DDB18(s32 arg0) {
    s32 *temp_s0;
    s32 *temp_v0;
    s32 temp_v0_2;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0xA0);
    D_003878D4 = temp_v0;
    memset(temp_v0, 0, 0xA0);
    temp_s0 = D_003878D4;
    temp_v0_2 = func_00126460(0x112);
    *temp_s0 = temp_v0_2;
    EftTexSet_Load8(temp_s0 + 2, temp_v0_2);
    D_003878D8 = BtlTask_CreateChildList(arg0, 0x14, 0xD0);
}
