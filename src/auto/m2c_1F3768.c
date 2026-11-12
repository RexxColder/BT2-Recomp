#include "m2c_macros.h"

void *BtlPool_Alloc(s32, M2C_UNK);                  /* extern */
s32 BtlPool_GetCurrent();                           /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *gEftVram;

void func_001F3768(void) {
    void *temp_v0;

    temp_v0 = BtlPool_Alloc(BtlPool_GetCurrent(), 0x80C);
    gEftVram = temp_v0;
    memset(temp_v0, 0, 0x80C);
    M2C_FIELD(gEftVram, s32 *, 0x804) = 0x2B00;
    M2C_FIELD(gEftVram, s32 *, 0x808) = 0x2A00;
}
