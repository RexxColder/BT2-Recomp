#include "common.h"

s32 func_00202DC0(s32 arg0);

/* returns (obj->flags64 at +0x28 & mask) != 0; obj = func_00202DC0(arg0) */
s32 func_00203C58(s32 arg0, s64 arg1) {
    s64 *obj = (s64 *)func_00202DC0(arg0);
    return (obj[5] & arg1) != 0;
}
