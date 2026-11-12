#include "common.h"

/* GUESS arity: func_00211288 gets arg0 (a0 passed through in the asm); ctx.h says 0 */
s32 func_00211288(s32 arg0);
s32 func_00203188(s32 arg0);
s32 func_00202E60(s32 arg0, s32 arg1);
extern s32 D_00387930;

s32 func_00203D08(u32 arg0) {
    s32 t;

    if (D_00387930 != 0 && arg0 < 2U) {
        t = func_00211288((s32)arg0);
        return func_00202E60(t, func_00203188(t));
    }
    return 0;
}
