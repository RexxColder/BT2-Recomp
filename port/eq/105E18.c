#include "common.h"

s32 func_00105A88(void);
extern u8 *D_003876A0;

s32 func_00105E18(void) {
    s32 *t = (s32 *)func_00105A88();
    s32 v = 1;

    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 2)) {
        v = (*t & 1) != 0;
    }
    return v;
}
