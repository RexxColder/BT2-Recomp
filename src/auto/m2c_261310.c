#include "m2c_macros.h"

void *func_00261060(s32);                           /* extern */
extern s32 D_003B2654 __attribute__((section(".data")));

void func_00261310(s32 arg0, s32 arg1) {
    s32 temp_a0;
    void *temp_v0;
    void *temp_v0_2;

    temp_a0 = arg0 & 0xFFFF;
    if (!(D_003B2654 & 0x100)) {
        if (arg1 != 0) {
            temp_v0 = func_00261060(temp_a0);
            M2C_FIELD(temp_v0, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_v0, s32 *, 0xAF0) | 0x10000000);
            return;
        }
        temp_v0_2 = func_00261060(temp_a0);
        M2C_FIELD(temp_v0_2, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_v0_2, s32 *, 0xAF0) & 0xEFFFFFFF);
    }
}
