#include "m2c_macros.h"

s32 *BtlPool_Alloc(s32, M2C_UNK);                   /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK EftTexSet_Load32(s32 *, s32);               /* extern */
s32 func_00126460(M2C_UNK);                         /* extern */
void *memset(void *, s32, s32);                     /* extern */
extern s32 *D_00387818;

// Allocates the 0x210-byte battle record from BtlPool, zeroes it, loads a texture set (id 0x11D) into +8 and creates a child task list (4, 0x340).
void func_001A17B8(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x210);
    D_00387818 = temp_v0;
    memset(temp_v0, 0, 0x210);
    EftTexSet_Load32((s32 *)((char *)D_00387818 + 8), func_00126460(0x11D));
    *D_00387818 = BtlTask_CreateChildList(arg0, 4, 0x340);
}
