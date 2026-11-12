#include "common.h"

s32 EftShot_TestBits(s32 arg0, s32 arg1);
s64 func_0014F0A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                   s32 arg7, s32 arg8, s32 arg9);

void func_00164AA0(s32 arg0, s32 arg1, s32 *arg2) {
    s32 sp10;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s5;
    s32 s6;
    s32 s7;
    s32 ret;

    s6 = 0;
    s0 = *(s32 *)(arg1 + 0x38);
    s7 = *(s32 *)(s0 + 0x80);
    sp10 = 0;
    s3 = (EftShot_TestBits(*(s32 *)s7, 0x10) != 0) ? 0x10 : 0;
    s3 = (EftShot_TestBits(*(s32 *)s7, 0x20) != 0) ? (s3 | 0x20) : s3;
    s3 = (EftShot_TestBits(*(s32 *)s7, 0x40) != 0) ? (s3 | 0x40) : s3;
    do {
        s5 = *arg2 + sp10;
        s1 = 0;
        if (*(u8 *)s5 != 0) {
            s2 = s0 + 0x84;
            do {
                ret = func_0014F0A8(arg0, (s32)arg2, s2, s6, s1, *(s32 *)(s0 + 0) & 1,
                                    *(s32 *)(s0 + 0) & 4, s3);
                if (ret != 0) {
                    func_001513D0(*(f32 *)(s0 + 0x10), s7, (s32)arg2, s2, s0 + 0x830, s0 + 0x50,
                                  s0 + 0x20, s6, s1, s1, ret);
                }
                s1 += 1;
            } while (s1 < *(u8 *)s5);
        }
        s6 += 1;
        sp10 += 0x110;
    } while (s6 < 0x10);
}
