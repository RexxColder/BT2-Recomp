#include "common.h"

/* GUESS arity: func_0032EB60 gets a0 (pass-through) and a1 (buf); ctx.h says 0 */
void func_0032EB60(s32 arg0, s32 *buf);
s32 func_0032EBD0(s32 arg0);

s32 func_002EE470(s32 arg0) {
    s32 buf[12];
    s32 ret;

    ret = 0;
    if (arg0 != 0) {
        func_0032EB60(arg0, buf);
        if (buf[0] != 8 && buf[0] != 0xC) {
            ret = func_0032EBD0(arg0);
        }
    }
    return ret;
}
