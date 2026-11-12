#include "m2c_macros.h"

s32 *BtlPool_Alloc(s32, M2C_UNK);                   /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK EftTexSet_Load32(s32 *, s32);               /* extern */
s32 func_00126460(M2C_UNK);                         /* extern */
M2C_UNK func_001E8B20();                            /* extern */
M2C_UNK memset(s32 *, M2C_UNK, M2C_UNK);            /* extern */
extern s32 *D_003878F4;

// Allocates a 0x1298-byte object into D_003878F4, loads texture 0x1 into it, creates child task list, then calls func_001E8B20.
void func_001E7670(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x1298);
    D_003878F4 = temp_v0;
    memset(temp_v0, 0, 0x1298);
    EftTexSet_Load32(D_003878F4 + 2, func_00126460(1));
    *D_003878F4 = BtlTask_CreateChildList(arg0, 2, 0xA0);
    func_001E8B20();
}
