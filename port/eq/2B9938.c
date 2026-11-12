#include "common.h"

extern u8 D_00379538[];
s32 Rand_Range(s32 arg0, s32 arg1);

s32 func_002B9938(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        return 0;
    }
    if (arg0 != 1) {
        Rand_Range((s32)D_00379538, arg1);
    }
    return 1;
}
