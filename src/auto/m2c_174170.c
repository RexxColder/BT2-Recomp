#include "m2c_macros.h"

void *BtlPool_Alloc(s32, s32);                      /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
s32 BtlTask_CreateChildList(s32, M2C_UNK, M2C_UNK); /* extern */
s32 func_00126580();                                /* extern */
M2C_UNK memset(void *, M2C_UNK, s32);               /* extern */
extern void *gEftTechEvt;

void func_00174170(s32 arg0) {
    s32 temp_s0;
    s32 temp_s0_2;
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0xC);
    gEftTechEvt = temp_v0;
    memset(temp_v0, 0, 0xC);
    M2C_FIELD(gEftTechEvt, s32 *, 8) = func_00126580();
    temp_s0 = M2C_FIELD(gEftTechEvt, s32 *, 8);
    temp_s0_2 = temp_s0 * 0x10;
    M2C_FIELD(gEftTechEvt, void **, 4) = BtlPool_Alloc(BtlPool_GetCurrent(), temp_s0_2);
    memset(M2C_FIELD(gEftTechEvt, void **, 4), 0, temp_s0_2);
    M2C_FIELD(gEftTechEvt, s32 *, 0) = BtlTask_CreateChildList(arg0, 6, 0x1C);
}
