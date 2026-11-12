#include "common.h"

extern s32 D_003877B8;

void func_0018E3A0(u8 *arg0, f32 farg0) {
    u8 *t;

    if (D_003877B8 != 0 && arg0 != NULL) {
        t = *(u8 **)(arg0 + 0x38);
        if (t != NULL && (*(u16 *)(t + 0x56) & 2)) {
            *(f32 *)(t + 0x34) = farg0 * 30.0f;
        }
    }
}
