#include "common.h"

extern s32 D_003877B8;

void func_0018E5E0(u8 *arg0, s32 arg1) {
    u8 *t;

    if (D_003877B8 != 0 && arg0 != NULL) {
        t = *(u8 **)(arg0 + 0x38);
        if (t != NULL && (*(u16 *)(t + 0x56) & 2)) {
            *(s8 *)(t + 0x54) = (s8)arg1;
        }
    }
}
