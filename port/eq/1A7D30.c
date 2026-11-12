#include "common.h"

extern u8 *gEftStruggle;

f32 func_001A7D30(s32 pad, s32 arg1) {
    if (arg1 != 0) {
        return 0.0f;
    }
    if (gEftStruggle == NULL) {
        return 25.0f;
    }
    return *(f32 *)(gEftStruggle + 0x630) + 15.0f;
}
