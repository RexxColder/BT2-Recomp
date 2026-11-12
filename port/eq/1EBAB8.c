#include "common.h"

void func_001EBAB8(u8 *arg0, f32 farg0) {
    u8 *t;

    if (arg0 == NULL) {
        return;
    }
    if (*(s32 *)(*(u8 **)(arg0 + 0x28)) != (s32)0x001EB270) {
        return;
    }
    t = *(u8 **)(arg0 + 0x38);
    if (t != NULL && (*(u16 *)(t + 0x60) & 1)) {
        *(f32 *)(t + 0x50) = farg0;
    }
}
