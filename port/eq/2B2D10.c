#include "common.h"

void func_002B2D10(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 *arg5, s32 *arg6);

/* 0x002B2D10: arg0 = {type, value, ?, ?, ?, scale}. scale
   (0 -> 1); v = value (+0x3FFF when negative) >> 14; out1 = (v * scale) << 11. type 2: out2..out6 = 0.
   type 3: out3 = (v << 10) + 0x800, out4..out6 = 0. Other types: out3 = (v << 10) + 0x800, out4..6 = 0x5DCC, 0x5F0C, 0x81C0. */
void func_002B2D10(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 *arg5, s32 *arg6) {
    s32 scale;
    s32 t;
    s32 q;

    scale = (arg0[5] > 0) ? arg0[5] : 1;
    t = arg0[1];
    if (t < 0) {
        t += 0x3FFF;
    }
    q = t >> 14;
    if (arg0[0] == 2) {
        *arg1 = (q * scale) << 11;
        *arg2 = 0;
        *arg3 = 0;
        *arg4 = 0;
        *arg5 = 0;
        *arg6 = 0;
    } else if (arg0[0] == 3) {
        *arg1 = (q * scale) << 11;
        *arg2 = 0;
        *arg3 = (q << 10) + 0x800;
        *arg4 = 0;
        *arg5 = 0;
        *arg6 = 0;
    } else {
        *arg1 = (q * scale) << 11;
        *arg2 = 0;
        *arg3 = (q << 10) + 0x800;
        *arg4 = 0x5DCC;
        *arg5 = 0x5F0C;
        *arg6 = 0x81C0;
    }
}
