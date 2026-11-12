#include "m2c_macros.h"

M2C_UNK func_0025FE58(void *, s32);                      /* extern */

void func_002AF578(void *arg0, s32 arg1) {
    void *temp_a0;
    void *temp_v1;

    func_0025FE58(M2C_FIELD(arg0, void **, 0), arg1);
    M2C_FIELD(arg0, s32 *, 0x18C) = arg1;
    temp_a0 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_a0, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_a0, s32 *, 0xAF0) & ~0x20);
    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xAF0) & ~0x40);
    M2C_FIELD(arg0, s8 *, 0x190) = 1;
    M2C_FIELD(arg0, s8 *, 0x191) = 0;
}
