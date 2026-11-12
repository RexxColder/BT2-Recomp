#include "common.h"

s32 func_0026CCF8(s32 arg0, s32 arg1, s32 arg2);

void func_0026E288(s32 arg0, s32 arg1) {
    s32 temp_s1;
    u8 temp_v1;
    u8 var_v0;

    temp_s1 = *(s32 *) (arg0 + 8) + arg1;
    if ((temp_s1 >= 0) && (func_0026CCF8(*(s32 *) (arg0 + 4), temp_s1, 0) != 0)) {
        temp_v1 = *(u8 *) (arg0 + 0x11);
        if (!(temp_v1 & 2)) {
            *(s32 *) (arg0 + 8) = temp_s1;
            if (arg1 == 1) {
                var_v0 = temp_v1 | 2;
            } else {
                var_v0 = temp_v1 | 0x10;
            }
            *(u8 *) (arg0 + 0x11) = var_v0;
        }
    }
}
