#include "common.h"

s32 func_002C34A0(u8 *arg0) {
    if (arg0 == 0) {
        return -1;
    }
    return *(s32 *)(*(u8 **)(arg0 + 0x1F7C) + 0x38);
}
