#include "m2c_macros.h"

M2C_UNK func_002DA708(void *, s32, s32);            /* extern */
M2C_UNK func_002DCA58(void *);                      /* extern */
M2C_UNK func_002DCD90(void *);                      /* extern */
M2C_UNK func_002DCDA8(void *);                      /* extern */
M2C_UNK func_002DCDD0(void *);                      /* extern */
extern M2C_UNK func_002DA9D0 __attribute__((section(".data")));

void *BtlOpp_GetObjId(void *arg0) {
    func_002DA708(arg0, 0, 0x40);
    M2C_FIELD(arg0, s32 *, 0) = 2;
    func_002DCA58(arg0 + 4);
    M2C_FIELD(arg0, s32 *, 0x10) = 2;
    func_002DCD90(arg0 + 0x18);
    func_002DCDA8(arg0 + 0x28);
    func_002DCDA8(arg0 + 0x48);
    func_002DCDA8(arg0 + 0x68);
    func_002DCDA8(arg0 + 0x88);
    func_002DCDD0(arg0 + 0xA8);
    M2C_FIELD(arg0, s32 *, 0xD0) = 0;
    M2C_FIELD(arg0, s32 *, 0xD8) = 0;
    M2C_FIELD(arg0, s32 *, 0xDC) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0xD4) = &func_002DA9D0;
    M2C_FIELD(arg0, s32 *, 0xE0) = 0;
    M2C_FIELD(arg0, s32 *, 0xE4) = 0;
    M2C_FIELD(arg0, s32 *, 0xE8) = 0;
    return arg0;
}
