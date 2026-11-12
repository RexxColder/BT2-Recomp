#include "common.h"

s32 func_00195A18(s32 arg0);

s32 func_001564B8(u8 *arg0) {
    u8 *s1;
    s32 *s0;
    s32 i;
    s32 found;
    s32 v;

    i = 0;
    found = 0;
    s1 = *(u8 **)(arg0 + 0x38);
    if (*(s32 *)(s1 + 0xAA0) > 0) {
        s0 = (s32 *)(s1 + 0xAA4);
        v = *(s32 *)(s1 + 0xAA4);
        do {
            s0++;
            if (v != 0) {
                if (func_00195A18(v) != 0) {
                    found = 1;
                }
            }
            i++;
            if (i < *(s32 *)(s1 + 0xAA0)) {
                v = *s0;
            } else {
                break;
            }
        } while (1);
    }
    return found & 0xFF;
}
