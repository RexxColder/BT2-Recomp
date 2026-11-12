#include "common.h"

/* GUESS arity: F1F78 and F2CA0 take (arg0, arg1) pass-through in the asm; ctx.h says 1 */
s32 func_002F1F10(s32 arg0, s32 arg1);
s32 func_002F1F78(s32 arg0, s32 arg1);
s32 func_002F2CA0(s32 arg0, s32 arg1);

s32 func_002BD4C0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;
    s32 temp_v0;

    switch (arg2) {
    case 0:
        func_002F1F10(arg0, arg1);
        break;
    case 1:
        temp_v0 = func_002F1F78(arg0, arg1);
        func_002F1F10(arg0, temp_v0 + arg1);
        break;
    case 2:
        temp_v0 = func_002F2CA0(arg0, arg1);
        temp_a1 = temp_v0 + 0x7FF;
        func_002F1F10(arg0, ((s32)((temp_a1 < 0) ? (temp_v0 + 0xFFE) : temp_a1) >> 11) + arg1);
        break;
    }
    return 0;
}
