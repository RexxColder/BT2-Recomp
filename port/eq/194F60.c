#include "common.h"

s32 func_00194F60(u8 *arg0, f32 farg0) {
    u8 *t;

    if (arg0 == NULL) {
        return 0;
    }
    if (*(s32 *)(*(u8 **)(arg0 + 0x28)) != (s32)0x00194948) {
        return 0;
    }
    t = *(u8 **)(arg0 + 0x38);
    if (*(s32 *)(t + 0x60) & 1) {
        *(f32 *)(t + 0x14) = farg0;
        return 1;
    }
    return 0;
}
