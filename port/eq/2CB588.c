#include "common.h"

void func_0032ECA0(s32 arg0);
s32 func_0032EC80(s32 arg0);

/* 0x002CB588: func_0032ECA0(obj+0x40) first; v = ((obj+0xC + obj+0x10) << 11) + obj+0x14, rem = v % obj+0x18;
 * lim = ((obj+8 - obj+0x10) << 11) - 0x1000 - obj+0x14. If obj+0x18 - rem < lim the four outputs use obj+0 and the
 * remainder, else lim and zeros. Ends with the tail call func_0032EC80(obj+0x40). */
s32 func_002CB588(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    s32 d;
    s32 rem;
    s32 lim;
    s32 a0v;
    s32 v;

    func_0032ECA0(*(s32 *)(arg0 + 0x40));
    v = ((*(s32 *)(arg0 + 0xC) + *(s32 *)(arg0 + 0x10)) << 11) + *(s32 *)(arg0 + 0x14);
    d = *(s32 *)(arg0 + 0x18);
    rem = v % d;
    lim = ((*(s32 *)(arg0 + 0x8) - *(s32 *)(arg0 + 0x10)) << 11) - 0x1000 - *(s32 *)(arg0 + 0x14);
    a0v = d - rem;
    if (a0v < lim) {
        *arg2 = a0v;
        *arg1 = *(s32 *)arg0 + rem;
        *arg3 = *(s32 *)arg0;
        *arg4 = lim - (*(s32 *)(arg0 + 0x18) - rem);
    } else {
        *arg2 = lim;
        *arg1 = *(s32 *)arg0 + rem;
        *arg3 = 0;
        *arg4 = 0;
    }
    return func_0032EC80(*(s32 *)(arg0 + 0x40));
}
