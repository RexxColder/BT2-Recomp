#include "common.h"

extern s32 D_003877B0;

void func_00187C10(u8 *arg0, f32 farg0) {
    u8 *t;

    if (D_003877B0 != 0 && arg0 != NULL) {
        t = *(u8 **)(arg0 + 0x38);
        if (t != NULL && (*(s32 *)(t + 0x19C) & 2)) {
            *(f32 *)(t + 0x84) = farg0 * 30.0f;
        }
    }
}
