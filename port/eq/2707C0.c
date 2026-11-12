#include "common.h"

s32 strcmp(s32 arg0, s32 arg1);

void func_002707C0(s32 arg0, s32 arg1, f32 farg0, f32 farg1) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;

    s2 = *(s32 *)(arg0 + 0) + (*(s32 *)(arg1 + 0) * 0xC0);
    *(f32 *)(s2 + 0x58) = farg0;
    *(f32 *)(s2 + 0x5C) = farg1;
    *(s32 *)(s2 + 0x48) = *(s32 *)(s2 + 0x48) | 0x10;
    s1 = *(s32 *)(arg1 + 4);
    s3 = 1;
    if (s1 == 0) {
        return;
    }
    if (!((u32)s3 < (u32)(*(s32 *)(arg0 + 4) - *(s32 *)(arg1 + 0)))) {
        return;
    }
    s0 = s2 + 0xC0;
    for (;;) {
        if (strcmp(s0, s2) == 0) {
            *(f32 *)(s0 + 0x58) = farg0;
            *(f32 *)(s0 + 0x5C) = farg1;
            *(s32 *)(s0 + 0x48) = *(s32 *)(s0 + 0x48) | 0x10;
            s1 -= 1;
            if (s1 == 0) {
                return;
            }
        }
        s3 += 1;
        if (!((u32)s3 < (u32)(*(s32 *)(arg0 + 4) - *(s32 *)(arg1 + 0)))) {
            return;
        }
        s0 += 0xC0;
    }
}
