#include "common.h"

#define FIELD_S32(p, off) (*(s32 *)((u8 *)(p) + (off)))

s32 func_002CB288(void *arg0, s32 arg1);
void func_002CB340(s32 arg0);
void func_002CB3A8(s32 arg0, s64 arg1, s32 arg2, s32 arg3);
void func_0032EC80(s32 arg0);
void func_0032ECA0(s32 arg0);

s32 func_002CB748(void *arg0) {
    s32 s0v;
    s32 s2;
    s32 s3;
    s32 s5;
    s32 s7;
    s32 n;
    s32 v1;
    s32 v0;
    s32 hi;
    s32 hi2;
    s32 hi3;
    s32 a0v;
    s32 a3v;

    s7 = 0;
    func_0032ECA0(FIELD_S32(arg0, 0x40));
    if (FIELD_S32(arg0, 0x44) == 0) {
        func_0032EC80(FIELD_S32(arg0, 0x40));
        return 0;
    }
    func_002CB340(5);
    s5 = *(s32 *)0x1000B400;
    n = FIELD_S32(arg0, 8);
    v1 = FIELD_S32(arg0, 0xC);
    hi = ((func_002CB288(arg0, *(s32 *)0x1000B410) + n) - v1) % n;
    v0 = FIELD_S32(arg0, 0x10) - hi;
    FIELD_S32(arg0, 0x10) = v0;
    hi2 = (v1 + hi) % n;
    FIELD_S32(arg0, 0xC) = hi2;
    a3v = hi2 + v0;
    a0v = FIELD_S32(arg0, 0x14);
    s3 = ((a0v < 0) ? (a0v + 0x7FF) : a0v) >> 11;
    s0v = a3v % n;
    FIELD_S32(arg0, 0x14) = a0v - (s3 << 11);
    if (s3 > 0) {
        hi3 = ((a3v + n) - 1) % n;
        s7 = 1;
        func_002CB3A8(FIELD_S32(arg0, 4) + (hi3 * 0x10), FIELD_S32(arg0, 0) + (hi3 << 11), 3, 0x80);
    }
    s2 = 0;
    if (s3 > 0) {
        do {
            func_002CB3A8(FIELD_S32(arg0, 4) + (s0v * 0x10), FIELD_S32(arg0, 0) + (s0v << 11),
                          ((s2 ^ (s3 - 1)) != 0) ? 3 : 0, 0x80);
            s2 += 1;
            s0v = (s0v + 1) % FIELD_S32(arg0, 8);
        } while (s2 < s3);
    }
    v0 = FIELD_S32(arg0, 0x10) + s3;
    FIELD_S32(arg0, 0x10) = v0;
    if (v0 != 0) {
        if (s7 != 0) {
            s5 = (s5 & 0x0FFFFFFF) | 0x30000000;
        }
        func_002CB340(s5 | 0x100);
    }
    func_0032EC80(FIELD_S32(arg0, 0x40));
    return 1;
}
