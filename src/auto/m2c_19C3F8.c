#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK EftTexSet_Load32(void *, s32);              /* extern */
s32 func_00126460(M2C_UNK);                         /* extern */
M2C_UNK func_001EC288(void *, s32);                 /* extern */
M2C_UNK func_001EC308(void *, void *);              /* extern */
M2C_UNK func_001EC370(void *, M2C_UNK);             /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *gEftGeyserMgr;

void func_0019C3F8(s32 arg0) {
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x2A0);
    gEftGeyserMgr = temp_v0;
    memset(temp_v0, 0, 0x2A0);
    M2C_FIELD(gEftGeyserMgr, s32 *, 0x298) = func_00126460(0x8F);
    M2C_FIELD(gEftGeyserMgr, s32 *, 0x29C) = func_00126460(0x90);
    EftTexSet_Load32(gEftGeyserMgr + 0x90, M2C_FIELD(gEftGeyserMgr, s32 *, 0x29C));
    func_001EC288(gEftGeyserMgr + 0x10, M2C_FIELD(gEftGeyserMgr, s32 *, 0x298));
    func_001EC308(gEftGeyserMgr + 0x10, gEftGeyserMgr + 0x90);
    func_001EC370(gEftGeyserMgr + 0x10, 0);
    M2C_FIELD(gEftGeyserMgr, s32 *, 0) = BtlTask_CreateChildList(arg0, 0x10, 0xC30);
}
