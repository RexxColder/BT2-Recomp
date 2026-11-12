#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern M2C_UNK D_00342430 __attribute__((section(".data")));
extern void *D_0038781C;
extern s32 D_00387820;

void func_001A4728(s32 arg0) {
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0xC);
    D_0038781C = temp_v0;
    memset(temp_v0, 0, 0xC);
    M2C_FIELD(D_0038781C, void **, 0) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x76C0);
    memset(M2C_FIELD(D_0038781C, void **, 0), 0, 0x76C0);
    M2C_FIELD(D_0038781C, M2C_UNK **, 8) = &D_00342430;
    D_00387820 = BtlTask_CreateChildList(arg0, 0x28, 0x160);
}
