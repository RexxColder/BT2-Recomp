#include "common.h"

void func_001959C8(s32 arg0);

s32 func_00156650(u8 *arg0) {
    u8 *s1 = *(u8 **)(arg0 + 0x38);
    s32 i = 0;

    if (*(s32 *)(s1 + 0xAA0) > 0) {
        do {
            s32 w = *(s32 *)(s1 + 0xAA4 + i * 4);

            i += 1;
            if (w != 0) {
                func_001959C8(w);
            }
        } while (i < *(s32 *)(s1 + 0xAA0));
    }
    return 0;
}
