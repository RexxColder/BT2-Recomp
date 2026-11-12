#include "common.h"

/* GUESS arity: func_002ECBA8 gets 7 args (a0..a3, t0..t2), func_002F1D30 gets 5 (a0..a3, t0) */
s32 func_002ECBA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_002ECD70(s32 arg0);
void func_002F1D30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002F1ED0(s32 arg0);
void func_002F1E48(s32 arg0);

s32 func_002EB8D8(s32 arg0, s32 arg1, s32 arg2) {
    s32 fr[68];
    u8 *s1;
    s32 temp;
    s32 v;

    s1 = (u8 *)arg0;
    v = func_002ECBA8(arg1, arg2, (s32)fr, (s32)&fr[64], (s32)&fr[65], (s32)&fr[66], (s32)&fr[67]);
    if (v < 0) {
        return -3;
    }
    *(s32 *)(s1 + 0x38) = fr[64];
    *(s32 *)(s1 + 0x34) = fr[65];
    temp = func_002ECD70(arg1);
    *(s32 *)(s1 + 0x18) = 0;
    *(s32 *)(s1 + 0x44) = fr[66];
    *(s32 *)(s1 + 0x3C) = temp;
    *(s32 *)(s1 + 0x40) = fr[65];
    func_002F1D30(*(s32 *)(s1 + 4), temp, *(s32 *)(s1 + 0x38), fr[65], fr[66]);
    if (func_002F1ED0(*(s32 *)(s1 + 4)) != 4) {
        *(s32 *)(s1 + 0xC) = fr[66];
        *(s64 *)(s1 + 0x10) = (s64)fr[67];
        return 0;
    }
    func_002F1E48(*(s32 *)(s1 + 4));
    return -1;
}
