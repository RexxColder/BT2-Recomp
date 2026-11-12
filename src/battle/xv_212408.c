#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002411E0(s32 arg0, s32 arg1);
s32 func_002412A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002413C0(s32 arg0, s32 arg1, s32 arg2);
f32 func_00241B20(s32 arg0, s32 arg1);

/* arg2 picks func_002413C0 (nonzero) or func_002412A0 (zero) on (arg1, arg3 & 0xFF) (first argument arg0); the result s0
 * is cut by 40% (flag 0x20000 of func_00211310(arg0, 7, ..)) or raised by 20% (flag 0x800, arg1 != 4), scaled by
 * (1 + (+0xAC4 - 1) / 2) when func_002411E0 has 0x40000 and +0xAC4 > 0, and returned as
 * s0 + s0 * (+0xA30 * (func_00241B20(arg0, arg1) - 1)) */
s32 func_00212408(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 s0;
    s32 a3m = arg3 & 0xFF;
    f32 f;
    f32 sf;
    if (arg2 & 0xFF) {
        s0 = func_002413C0(arg0, arg1, a3m);
    } else {
        s0 = func_002412A0(arg0, arg1, a3m);
    }
    if (func_00211310(arg0, 7, 0x20000) != 0) {
        s0 = s0 - ((s0 * 4) / 10);
    } else if ((func_00211310(arg0, 0, 0x800) != 0) && (arg1 != 4)) {
        s0 = s0 + (s0 / 5);
    }
    if ((func_002411E0(arg0, arg1) & 0x40000) && (*(f32 *)((u8 *)arg0 + 0xAC4) > 0.0f)) {
        f = *(f32 *)((u8 *)arg0 + 0xAC4);
        s0 = (s32)((f32)s0 * (((f - 1.0f) * 0.5f) + 1.0f));
    }
    f = func_00241B20(arg0, arg1);
    sf = (f32)s0;
    return (s32)(sf + (sf * (*(f32 *)((u8 *)arg0 + 0xA30) * (f - 1.0f))));
}
