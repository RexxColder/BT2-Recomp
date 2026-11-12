#include "common.h"

s32 strlen(s32 arg0);
s32 func_002FEEA0(s32 arg0, s32 arg1);

s32 func_002FEEF8(s8 *arg0, s8 *arg1) {
    s32 len0;
    s32 len1;
    s32 i;

    len0 = strlen((s32)arg0);
    len1 = strlen((s32)arg1);
    if (len0 != len1) {
        return -1;
    }
    for (i = 0; i < len0; i++) {
        if (func_002FEEA0(arg0[i], arg1[i]) != 0) {
            return -1;
        }
    }
    return 0;
}
