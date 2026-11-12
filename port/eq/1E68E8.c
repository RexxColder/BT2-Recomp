#include "common.h"

void func_001E68E8(u8 *arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    u8 *t;

    if (arg0 != NULL) {
        t = *(u8 **)(arg0 + 0x38);
        if ((*(s64 *)(t + 0) & 5) == 1) {
            *(f32 *)(t + 0x3C) = farg3;
            *(s32 *)(t + 0x24) = arg1;
            *(f32 *)(t + 0x30) = farg0;
            *(f32 *)(t + 0x34) = farg1;
            *(f32 *)(t + 0x38) = farg2;
        }
    }
}
