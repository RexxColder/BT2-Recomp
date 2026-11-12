#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlScene_GetPackEntry(s32, M2C_UNK);            /* extern */
M2C_UNK BtlTask_CreateChildList(void *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK EftTexSet_Load32(void *, s32);              /* extern */
M2C_UNK func_00148000(M2C_UNK);                     /* extern */
M2C_UNK func_0014E258(void *, void *);              /* extern */
M2C_UNK func_001EC288(void *, s32);                 /* extern */
M2C_UNK func_001EC308(void *, void *);              /* extern */
M2C_UNK func_001EC370(void *, M2C_UNK);             /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void func_001766C8(void *arg0, void *arg1) {
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    func_00148000(0x1E98);
    memset(temp_s1, 0, 0x1E98);
    M2C_FIELD(temp_s1, s32 *, 0x1E80) = BtlScene_GetPackEntry(M2C_FIELD(arg1, s32 *, 0x1C), 2);
    M2C_FIELD(temp_s1, void **, 0x1E88) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x208);
    M2C_FIELD(temp_s1, void **, 0x1E84) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x80);
    memset(M2C_FIELD(temp_s1, void **, 0x1E88), 0, 0x208);
    memset(M2C_FIELD(temp_s1, void **, 0x1E84), 0, 0x80);
    M2C_FIELD(temp_s1, s32 *, 0x1E8C) = BtlScene_GetPackEntry(M2C_FIELD(arg1, s32 *, 0x1C), 0x19);
    M2C_FIELD(temp_s1, s32 *, 0x1E90) = BtlScene_GetPackEntry(M2C_FIELD(arg1, s32 *, 0x1C), 0x1A);
    func_0014E258(arg1, temp_s1);
    EftTexSet_Load32(M2C_FIELD(temp_s1, void **, 0x1E88), M2C_FIELD(temp_s1, s32 *, 0x1E90));
    func_001EC288(M2C_FIELD(temp_s1, void **, 0x1E84), M2C_FIELD(temp_s1, s32 *, 0x1E8C));
    func_001EC308(M2C_FIELD(temp_s1, void **, 0x1E84), M2C_FIELD(temp_s1, void **, 0x1E88));
    func_001EC370(M2C_FIELD(temp_s1, void **, 0x1E84), 0);
    BtlTask_CreateChildList(arg0, 2, 0xAE0);
}
