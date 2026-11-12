#include "common.h"

s32 func_003063E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* 0x002D7588(obj, a1, a2, out1, out2): p = obj + 0x28. When *p == 1 and *(p+4) != 0, the callee
 * func_003063E8(buf, a1, a2, buf + 0x10) runs with buf[0] = *(p+4), buf[1] = *(p+8), then *out1 = buf[4] and
 * *out2 = buf[5]. Otherwise *out1 = 0 when *p == 1 is false or *(p+4) == 0 is the case, and *out2 = 0. */
void func_002D7588(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4) {
    u8 *p = arg0 + 0x28;
    s32 buf[8];

    if (*(s32 *)p == 1 && *(s32 *)(p + 4) != 0) {
        buf[0] = *(s32 *)(p + 4);
        buf[1] = *(s32 *)(p + 8);
        func_003063E8((s32)buf, arg1, arg2, (s32)&buf[4]);
        *arg3 = buf[4];
        *arg4 = buf[5];
        return;
    }
    *arg3 = 0;
    *arg4 = 0;
}
