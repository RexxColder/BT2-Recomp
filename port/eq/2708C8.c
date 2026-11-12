#include "common.h"

s32 strcmp(u8 *arg0, u8 *arg1);

void func_002708C8(s32 *arg0, s32 *arg1, f32 farg0) {
    u8 *s2;
    u8 *s0;
    s32 s1;
    s32 s3;
    s32 n;
    f32 v;

    s2 = (u8 *)(arg0[0] + arg1[0] * 0xC0);
    if (1.0f < farg0) {
        *(f32 *)(s2 + 0x60) = 1.0f;
    } else if (!(farg0 < 0.0f)) {
        *(f32 *)(s2 + 0x60) = farg0;
    } else {
        *(f32 *)(s2 + 0x60) = 0.0f;
    }
    *(s32 *)(s2 + 0x48) = *(s32 *)(s2 + 0x48) | 0x20;

    s1 = arg1[1];
    s3 = 1;
    if (s1 == 0) {
        return;
    }
    n = arg0[1] - arg1[0];
    if (!((u32)n > 1U)) {
        return;
    }

    s0 = s2 + 0xC0;
    for (;;) {
        if (strcmp(s0, s2) == 0) {
            if (1.0f < farg0) {
                v = 1.0f;
            } else if (!(farg0 < 0.0f)) {
                v = farg0;
            } else {
                v = 0.0f;
            }
            *(f32 *)(s0 + 0x60) = v;
            s1 -= 1;
            *(s32 *)(s0 + 0x48) = *(s32 *)(s0 + 0x48) | 0x20;
            if (s1 == 0) {
                return;
            }
        }
        s3 += 1;
        s0 += 0xC0;
        if (!((u32)s3 < (u32)n)) {
            return;
        }
    }
}
