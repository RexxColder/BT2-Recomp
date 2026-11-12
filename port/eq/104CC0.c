#include "common.h"

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00100FC8(s32 arg0);
void func_00101FD0(void);
void func_00261B18(s32 arg0);
void func_00261D30(s32 arg0);
void func_00261F38(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_0028BAA8(s32 arg0);
extern u8 *D_003876A0;

s32 func_00104CC0(s32 *arg0) {
    u8 *s2;
    s32 s1;
    s32 s3;
    s32 d;
    s32 q;
    s32 v2;
    s32 a0b;
    s32 a0;
    s32 v1;

    v1 = *arg0;
    s2 = D_003876A0;
    if (v1 == 0) {
        s1 = 0;
        func_00261B18((s32)arg0);
        func_00261D30(0);
        *(s32 *)(s2 + 0xC) = func_0028BAA8(0x74800);
        s3 = 0;
        *(s32 *)(s2 + 0) = func_00100ED0(0x3C2B, 0, 1);
        do {
            d = *(s32 *)(D_003876A0 + s3 + 0x2AC);
            q = d / 9;
            func_00261F38(0, 1, s1 & 0xFFFF, d + 0xACBB, 0xACC1 + q * 9, 0xACC2 + q * 9);
            s3 += 0x1D0;
            s1 += 1;
        } while (s1 < 2);
        v2 = func_0028BAA8(0x6DC800);
        *(s32 *)(s2 + 4) = v2;
        if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
            a0 = *(s32 *)(D_003876A0 + 0xD4) + 0x3DF7;
        } else {
            a0 = *(s32 *)(D_003876A0 + 0xD4) + 0x3DE7;
        }
        *(s32 *)(s2 + 4) = func_00100ED0(a0, v2, 0);
        if (*(s32 *)(D_003876A0 + 0xB8) != 6) {
            a0b = 0x33CA;
        } else {
            a0b = 0x33CB;
        }
        *(s32 *)(s2 + 0x24) = func_00100ED0(a0b, 0, 0);
        func_00101FD0();
        func_00100FC8(1);
        *arg0 += 1;
        return 0;
    }
    if (v1 == 1) {
        return func_00100FC8(0) != 0;
    }
    return 1;
}
