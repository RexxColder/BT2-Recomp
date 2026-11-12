#include "m2c_macros.h"

void Dma_AddData(s32, M2C_UNK);                  /* extern */
void func_00271370();                            /* extern */
void func_002814D0(M2C_UNK, M2C_UNK, u16, M2C_UNK); /* extern */

/* Calls Dma_AddData, func_00271370, then func_002814D0 with 0x48 or 0x44 depending on the byte at +0x5A2 */
void func_00280988(void *arg0) {
    u8 flag;

    Dma_AddData(arg0 + 0x494, 0x10);
    func_00271370();
    flag = M2C_FIELD(arg0, u8 *, 0x5A2);
    if (flag != 0) {
        func_002814D0(0, 0x1C00, M2C_FIELD(arg0, u16 *, 0x4B4), 0x48);
        return;
    }
    func_002814D0(0, 0x1C00, M2C_FIELD(arg0, u16 *, 0x4B4), 0x44);
}
