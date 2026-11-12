#include "common.h"

extern s32 D_003877B4;

void func_0018BF08(u8 *arg0, f32 farg0) {
    u8 *t;

    if (D_003877B4 != 0 && arg0 != NULL) {
        t = *(u8 **)(arg0 + 0x38);
        if (t != NULL && (*(s32 *)(t + 0x1D8) & 2)) {
            *(f32 *)(t + 0x80) = farg0;
        }
    }
}
