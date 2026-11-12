#include "common.h"

s32 func_002E0EE8(s32 arg0);

s32 func_002D5E78(u8 *arg0, u32 arg1) {
    s32 temp_a2;

    temp_a2 = *(s32 *)(arg0 + 0x34);
    if (temp_a2 == 0x64) {
        return 0;
    }
    if (temp_a2 != (s32)arg1) {
        return 1;
    }
    if (arg1 < 6U) {
        if (arg1 == 2) {
            if (func_002E0EE8(*(s32 *)(arg0 + 0x30)) == 1) {
                return 1;
            }
            return 0;
        }
        if (arg1 == 0 || arg1 == 3) {
            return 1;
        }
        return 0;
    }
    if (arg1 != 0x15) {
        return 1;
    }
    return 0;
}
