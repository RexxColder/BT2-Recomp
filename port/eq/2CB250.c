#include "common.h"
s32 func_002CB250(u8 *arg0, u8 *arg1) {
    if (arg0 == 0) {
        return 1;
    }
    return *(s32 *)(arg1 + 0x38) < *(s32 *)(arg0 + 0x38);
}
