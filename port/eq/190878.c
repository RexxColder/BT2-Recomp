#include "common.h"

extern s32 D_003877BC;

void func_00190878(u8 *arg0, f32 farg0) {
    u8 *t;

    if (D_003877BC != 0 && arg0 != NULL) {
        t = *(u8 **)(arg0 + 0x38);
        if (t != NULL && (*(u16 *)(t + 0x44) & 2)) {
            *(f32 *)(t + 0x34) = farg0 * 30.0f;
        }
    }
}
