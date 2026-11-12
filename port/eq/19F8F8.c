#include "common.h"

s32 func_0019F8F8(u8 *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    if (*(s32 *)(*(u8 **)(arg0 + 0x28)) != (s32)0x0019FAC8) {
        return 0;
    }
    if (*(u8 *)(arg0 + 0) & 1) {
        return 0;
    }
    return *(s32 *)(*(u8 **)(arg0 + 0x38) + 0x30);
}
