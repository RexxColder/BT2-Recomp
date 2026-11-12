#include "common.h"

s32 func_001B8088(s32 arg0);
void func_001B80F0(f32 farg0, s32 arg0);
void func_001B8510(s32 arg0, s32 arg1);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_00312680(f32 farg0, s32 arg0, s32 arg1);
extern f32 D_00385038;
extern u8 *D_003876A0;

void func_001B7A28(s32 arg0) {
    u8 *e;
    u8 *s2;
    u8 *s0;
    f32 f20;
    f32 sp[4];
    s32 s1;
    s32 v;

    e = *(u8 **)(arg0 + 0x38);
    s2 = *(u8 **)(e + 0x68);
    f20 = *(f32 *)(e + 0x48);
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) == 0) {
        *(f32 *)(e + 0x54) = *(f32 *)(e + 0x54) + 1.0f;
        v = func_001B8088((s32)e);
        if (v > 0) {
            s1 = v;
            do {
                s1 -= 1;
                func_001B80F0(1.0f, (s32)e);
            } while (s1 != 0);
        }
        s1 = 9;
        do {
            if (*(s32 *)(s2 + 0x5C) & 1) {
                s0 = s2 + 0x20;
                func_00312680(f20, (s32)s0, (s32)s0);
                func_00312680(D_00385038, (s32)sp, (s32)(e + 0x20));
                func_00312638((s32)s0, (s32)s0, (s32)sp);
                func_00312638((s32)s2, (s32)s2, (s32)s0);
                func_001B8510((s32)e, (s32)s2);
            }
            s1 -= 1;
            s2 += 0x60;
        } while (s1 >= 0);
    }
}
