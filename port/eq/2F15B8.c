#include "common.h"

s32 func_002E7BB8(s32 arg0);

s32 func_002F15B8(u8 *arg0) {
    if (arg0 != NULL) {
        return func_002E7BB8(*(s32 *)(arg0 + 4));
    }
    return 0;
}
