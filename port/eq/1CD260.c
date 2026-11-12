#include "common.h"

void func_001CDA98(void *arg0, void *arg1, void *arg2);

void func_001CD260(u8 *arg0) {
    u8 *s1;
    u8 *s0;
    s32 a;

    s1 = *(u8 **)(arg0 + 0x38);
    for (a = 0; a < 2; a++) {
        *(s32 *)(s1 + a * 8 + 0x14) = 0;
        *(s32 *)(s1 + a * 8 + 0x10) = 0;
    }
    s0 = *(u8 **)(s1 + 0x124);
    if (s0 != NULL) {
        *(s16 *)(s0 + 4) = 0;
        do {
            func_001CDA98(s1 + 0x124, s1 + 0x128, s0);
            *(s32 *)(s1 + 0x118) = *(s32 *)(s1 + 0x118) - 1;
            s0 = *(u8 **)(s0 + 8);
            if (s0 != NULL) {
                *(s16 *)(s0 + 4) = 0;
            }
        } while (s0 != NULL);
    }
}
