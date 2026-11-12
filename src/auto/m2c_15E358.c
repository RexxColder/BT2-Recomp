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

void func_0015E358(void *arg0, void *arg1) {
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    func_00148000(0x1E90);
    memset(temp_s0, 0, 0x1E90);
    M2C_FIELD(temp_s0, void **, 0x1E84) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x208);
    M2C_FIELD(temp_s0, void **, 0x1E80) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x80);
    memset(M2C_FIELD(temp_s0, void **, 0x1E84), 0, 0x208);
    memset(M2C_FIELD(temp_s0, void **, 0x1E80), 0, 0x80);
    func_0014E258(arg1, temp_s0);
    M2C_FIELD(temp_s0, s32 *, 0x1E88) = BtlScene_GetPackEntry(M2C_FIELD(arg1, s32 *, 0x1C), 0x17);
    temp_v0 = BtlScene_GetPackEntry(M2C_FIELD(arg1, s32 *, 0x1C), 0x18);
    M2C_FIELD(temp_s0, s32 *, 0x1E8C) = temp_v0;
    EftTexSet_Load32(M2C_FIELD(temp_s0, void **, 0x1E84), temp_v0);
    func_001EC288(M2C_FIELD(temp_s0, void **, 0x1E80), M2C_FIELD(temp_s0, s32 *, 0x1E88));
    func_001EC308(M2C_FIELD(temp_s0, void **, 0x1E80), M2C_FIELD(temp_s0, void **, 0x1E84));
    func_001EC370(M2C_FIELD(temp_s0, void **, 0x1E80), 0);
    BtlTask_CreateChildList(arg0, 3, 0xAD0);
}
