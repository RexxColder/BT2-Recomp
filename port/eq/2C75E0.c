#include "common.h"

void func_002CF470(u8 *arg0, s32 arg1, s32 arg2, s64 *arg3, s64 *arg4, s32 arg5);
s64 func_002C76B0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s64 *arg5);

/* 0x002C75E0(obj, a1, a2, out64, out64b, t1): both 64-bit outputs are set to -1; when a2 != 0: func_002CF470(obj,
 * word obj+0x1FC8, a2, &r, out64b, t1) writes r; if r >= 0: out64 = func_002C76B0(obj+0xD30, word obj+0x1FC0 + 0x118,
 * a1, 0, t1, out64b). (GUESS: the a3 argument of the second call is whatever the callee left in $a3: 0 here.) */
void func_002C75E0(u8 *arg0, s32 arg1, s32 arg2, s64 *arg3, s64 *arg4, s32 arg5) {
    u8 *v = arg0 + 0x1FB8;
    s64 r = 0;
    u8 *s3;

    *(s64 *)arg3 = -1;
    *(s64 *)arg4 = -1;
    if (arg2 == 0) {
        return;
    }
    func_002CF470(arg0, *(s32 *)(v + 0x10), arg2, &r, arg4, arg5);
    if (r < 0) {
        return;
    }
    s3 = *(u8 **)(v + 0x8);
    *(s64 *)arg3 = func_002C76B0(arg0 + 0xD30, s3 + 0x118, arg1, 0, arg5, arg4);
}
