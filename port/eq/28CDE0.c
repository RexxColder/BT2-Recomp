#include "common.h"

/* GUESS arity: func_0028CB60 gets arg0 (a0 passed through in the asm); ctx.h says 0 */
s32 func_0028CB60(s32 arg0);
s64 litodp(s32 arg0);
s64 dpadd(s64 arg0, s64 arg1);
s64 dpmul(s64 arg0, s64 arg1);

void func_0028CDE0(s32 arg0) {
    s32 t;
    s64 v;

    t = func_0028CB60(arg0);
    v = litodp(t);
    if (t < 0) {
        v = dpadd(v, (s64)0x83E0 << 47);
    }
    dpmul(dpadd(v, (s64)0xFF80 << 46), (s64)0xF7C0 << 46);
}
