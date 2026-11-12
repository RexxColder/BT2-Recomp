#include "m2c_macros.h"

s32 Gsc_GetInt();                                   /* extern */
M2C_UNK func_00261080(s32, s32, s32);               /* extern */
extern s32 D_003B2680 __attribute__((section(".data")));

s32 func_002A5F38(s32 arg0) {
    s32 temp_a2;
    s32 temp_s0;
    s32 temp_s1;

    if (arg0 == 0) {
        temp_s0 = Gsc_GetInt();
        temp_s1 = Gsc_GetInt();
        temp_a2 = Gsc_GetInt();
        if (temp_s0 >= 0) {
            if (temp_s0 == 0) {
                D_003B2680 = temp_s1;
            }
            func_00261080(temp_s0 & 0xFFFF, temp_s1, temp_a2);
        }
    }
    return 1;
}
