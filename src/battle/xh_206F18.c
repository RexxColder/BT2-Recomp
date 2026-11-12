#include "m2c_macros.h"

M2C_UNK func_002070D8(void *, s32, s32);                    /* extern */
M2C_UNK func_00260A50(s32, void *);                 /* extern */
extern void *D_00387A40;

// For battle slot 0x142C (if valid), calls func_002070D8 on sub-structs +0x9A0/+0x9B0 of arg0 then func_00260A50 on the slot.
void func_00206F18(void *arg0) {
    s32 temp_a1;
    s32 temp_a1_2;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0x142C);
    if ((temp_a1 >= 0) && (temp_a1 < M2C_FIELD(D_00387A40, s32 *, 0xC))) {
        temp_a1_2 = M2C_FIELD(arg0, s32 *, 0x1530);
        func_002070D8(arg0, temp_a1_2 + 0x9A0, temp_a1_2 + 0x9B0);
        func_00260A50(M2C_FIELD(D_00387A40, s32 *, 8) + (M2C_FIELD(arg0, s32 *, 0x142C) * 0x1520), D_00387A40);
    }
}
