#include "m2c_macros.h"

M2C_UNK func_002CE390(void *);                      /* extern */
s32 func_002DA708(void *, s32, s32);             /* extern */

void func_002CE318(void *arg0) {
    func_002DA708(arg0, 0, 0x2A);
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    func_002CE390(arg0 + 0x38);
    func_002CE390(arg0 + 0x50);
    func_002CE390(arg0 + 0x68);
    func_002CE390(arg0 + 0x80);
}
