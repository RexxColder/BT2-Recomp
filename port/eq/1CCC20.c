#include "common.h"

s32 func_001CCC20(u8 *arg0, f32 farg0) {
    u8 *t;

    if (arg0 == NULL) {
        return 0;
    }
    if (*(s32 *)(*(u8 **)(arg0 + 0x28)) != (s32)0x001CC770) {
        return 0;
    }
    t = *(u8 **)(arg0 + 0x38);
    if (*(s32 *)(t + 0x40) & 1) {
        *(f32 *)(t + 0x60) = farg0;
        return 1;
    }
    return 0;
}
