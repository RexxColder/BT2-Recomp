#include "common.h"

s32 memcmp(void *arg0, void *arg1, s32 arg2);
extern u8 D_0037BAB0[] __attribute__((section(".data")));

s32 func_002E95E0(u8 *arg0, s32 arg1, s16 *arg2) {
    s32 temp_v1;
    s32 var_v0;

    var_v0 = 0;
    if (arg1 >= 0x10) {
        if ((arg0[1] | (arg0[0] << 8)) == 0x8000) {
            temp_v1 = (arg0[2] << 8) | arg0[3];
            if (arg1 > 0x7FFF) {
                var_v0 = 0;
                if (memcmp(arg0 + (temp_v1 - 2), D_0037BAB0, 6) == 0) {
                    if (arg2 != NULL) {
                        *arg2 = temp_v1 + 4;
                    }
                    var_v0 = 1;
                }
            }
        }
    }
    return var_v0;
}
