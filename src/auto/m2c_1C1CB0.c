#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTaskList_AddTail(s32, M2C_UNK *, M2C_UNK);   /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern M2C_UNK D_00342980 __attribute__((section(".data")));
extern void *D_00387898;

void func_001C1CB0(s32 arg0) {
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x128);
    D_00387898 = temp_v0;
    memset(temp_v0, 0, 0x128);
    M2C_FIELD(D_00387898, s32 *, 0) = BtlTask_CreateChildList(arg0, 1, 0x20D50);
    M2C_FIELD(D_00387898, s32 *, 4) = BtlTaskList_AddTail(M2C_FIELD(D_00387898, s32 *, 0), &D_00342980, 0);
}
