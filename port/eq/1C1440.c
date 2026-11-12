#include "common.h"

s32 func_001C1440(u8 *arg0) {
    s32 result = 0;
    if (arg0 != NULL) {
        s32 p = *(s32 *)(arg0 + 0x38);
        if (p != 0) {
            result = p + 0xAB0;
        }
    }
    return result;
}
