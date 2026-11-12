#include "common.h"

s32 Gsc_GetInt(s32 arg0);
extern s32 D_003B0C34 __attribute__((section(".data")));

s32 func_002A7B08(s32 arg0, s32 *arg1) {
    s32 temp_v0;

    if (arg0 == 1) {
        return 0;
    }
    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt(arg0);
        arg1[0] = 0;
        arg1[1] = temp_v0;
        return 0;
    }
    if (arg0 == 2) {
        if (arg1[0] != 0) {
            return 1;
        }
        if (D_003B0C34 & (1 << (arg1[1] & 31))) {
            arg1[0] = 1;
        }
        return 0;
    }
    return 0;
}
