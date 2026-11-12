#include "common.h"

s32 func_002D5B08(s32 arg0) {
    s32 v = 0xC0;

    if ((u32)(arg0 - 0xC0) >= 0x20U) {
        v = 0xE0;
        if ((u32)(arg0 - 0xE0) >= 0x10U) {
            v = 0xBD;
            if (arg0 != 0xBD) {
                v = 0;
                if (arg0 == 0xBF) {
                    v = 0xBD;
                }
            }
        }
    }
    return v;
}
