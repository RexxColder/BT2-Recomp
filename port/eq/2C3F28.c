#include "common.h"

#define W(p, off) (*(s32 *)((p) + (off)))
#define D64(p, off) (*(s64 *)((p) + (off)))

s32 func_002D07B0(u8 *arg0, s32 arg1);
s32 func_002C4590(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_002C3F28(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *s6;
    u8 *s0;
    s32 s4;
    s64 *q10;
    s64 *q18;

    s6 = arg0 + 0x1F74;
    if (func_002D07B0(arg0, 6) == 0) {
        return 1;
    }
    s0 = (u8 *)W(s6, 8);
    if (W(s0, 0x38) == -1) {
        W(s0, 0x38) = arg1;
    }
    if (W(s0, 0x30) == -1) {
        W(s0, 0x30) = arg1;
    }
    s4 = func_002D07B0(arg0, 0x1E);
    if (s4 != -1) {
        if (func_002D07B0(arg0, 0x37) != 0) {
            if (arg1 < W(s0, 0x28)) {
                W(s0, 0x38) = s4;
            }
        } else {
            if (arg1 == W(s0, 0x30)) {
                W(s0, 0x38) = s4;
            }
        }
    }

    W(s0, 0x28) = arg1;
    if (W(s0, 0x38) != arg1) {
        return 1;
    }
    if (arg4 >= 0) {
        q10 = (s64 *)(s0 + 0x10);
        q18 = (s64 *)(s0 + 0x18);
        if ((s64)arg4 < *q10) {
            *q10 = (s64)arg4;
        }
        if ((s64)arg4 < *q18) {
            *q18 = (s64)arg4;
        }
    }
    return func_002C4590(arg0, W(s6, 0x18), arg2, arg3, arg4);
}
