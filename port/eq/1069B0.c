#include "common.h"

s32 func_00106970(s32 arg0);

s32 func_001069B0(s32 arg0, s32 arg1) {
    s32 sel = (arg0 != 0) ? 7 : 0x3E;

    return func_00106970(sel + arg1);
}
