#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))

s32 func_002C2D60(void *arg0);
s32 func_002CFB98(void *arg0, void *arg1, s32 *arg2);
s32 func_002CFC18(void *arg0, void *arg1, s32 *arg2);
s32 func_002CFC98(void *arg0);
void func_002D03C8(void *arg0, s32 arg1);
s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);

void func_002CFA30(void *arg0) {
    s32 out[2];
    u8 *s0, *s1, *s2, *s3, *s4;
    s32 v, a0, a2, a1, v1;
    s32 ok = 1;

    s0 = (u8 *)FLD(arg0, 0x36B0);
    s3 = s0 + 0xC;
    s4 = s0 + 0x8A0;
    s1 = s0 + 0xAD0;
    s2 = s0 + 0xD0C;
    if (FLD(s0, 0) == 0 && func_002CFB98(arg0, s2, &out[0]) == 0 && func_002CFC18(arg0, s1, &out[1]) == 0) {
        if (func_002CFC98(arg0) != 0) {
            FLD(s0, 0x8A0) = 1;
            if (FLD(s3, 0) == 0) {
                a1 = FLD(s4, 4);
            } else {
                v = FLD(s3, 0xC);
                if (v > 0) {
                    a0 = FLD(s0, 0xDC4);
                    a2 = FLD(s3, 0x34);
                    if (a0 > 0 && a2 > 0) {
                        v = func_002E0A98(a0, 0x3E8, a2);
                    }
                    a1 = v;
                } else if (func_002C2D60(arg0) >= 0x6C) {
                    a1 = FLD(s4, 4);
                } else {
                    a1 = ((s32)((u32)FLD(s4, 4) << 11)) / 2018;
                }
            }
            v1 = FLD(s4, 8);
        } else if (out[1] != 0) {
            v1 = FLD(s1, 8);
            a1 = FLD(s1, 4);
        } else if (out[0] != 0) {
            v1 = FLD(s2, 8);
            a1 = FLD(s2, 4);
        } else {
            ok = 0;
        }
        if (ok) {
            FLD(s0, 4) = a1;
            FLD(s0, 0) = 1;
            FLD(s0, 8) = v1;
            func_002D03C8(arg0, a1);
        }
    }
}
