#include "common.h"

void EftRibbon_SetTexPair(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00129C28(s32 arg0, s32 arg1);
s32 rand(void);
extern u8 *D_003876A0;

void func_001C4FD0(void *arg0, void *arg1) {
    u8 *s0;
    u8 *s1;
    u8 *s2;
    s32 s3;
    s32 v0;
    s32 i;
    f32 f0;
    f32 f1;

    s0 = (u8 *)arg0;
    s2 = (u8 *)arg1;
    s1 = *(u8 **)(s2 + 0x38);
    s3 = *(s32 *)(s2 + 0x3C);
    f0 = *(f32 *)(s1 + 0xC);
    if ((f0 < 0.0f) || (f0 > 0.0f)) {
        *(s32 *)(s0 + 0x50) = *(s32 *)(s0 + 0x50) | 0x10;
    }
    if (s1[2] & 1) {
        if (!(rand() & 1)) {
            *(s32 *)(s0 + 0x50) = *(s32 *)(s0 + 0x50) | 0x20;
        }
    }
    func_00129C28((s32)(s0 + 0x90), (s32)(s2 + 0x10));
    *(s32 *)(s0 + 0x7C) = 0;
    func_00129C28((s32)(s0 + 0xA0), s3);
    *(s32 *)(s0 + 0xB0) = 0;
    *(s32 *)(s0 + 0xB4) = 0;
    *(s32 *)(s0 + 0xB8) = 0;
    *(s32 *)(s0 + 0xBC) = 0;
    if (s1[1] != 0) {
        v0 = 1;
        *(s32 *)(s0 + 0xC0) = v0;
        if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
            v0 = 6;
        } else {
            v0 = 0x10;
        }
    } else {
        f0 = *(f32 *)(s1 + 0xC);
        f1 = *(f32 *)(s0 + 0xB0);
        if (f0 < f1) {
            v0 = 4;
        } else if (!(f1 < f0)) {
            v0 = 3;
        } else {
            v0 = 4;
        }
        *(s32 *)(s0 + 0xC0) = v0;
        v0 = 0x20;
    }
    *(s32 *)(s0 + 0x5C) = v0;
    i = 0;
    if (*(s32 *)(s0 + 0xC0) > 0) {
        do {
            EftRibbon_SetTexPair((s32)s0, i, *(s32 *)(s2 + 0x34), *(s32 *)(s2 + 0x30) + i,
                                 *(s32 *)(s2 + 0x30) + i);
            i += 1;
        } while (i < *(s32 *)(s0 + 0xC0));
    }
}
