#include "common.h"

s32 func_002DCC38(s32 a0, s32 a1, s32 a2, void *a3, void *t0);
s32 func_002DCA68(s32 a0, s32 a1, s32 a2, void *a3, void *t0);

s32 func_002DA928(s32 arg0, s32 arg1, s32 arg2, void *arg3, void *arg4) {
    void *fp;

    *(s32 *)arg3 = 0;
    *(s32 *)arg4 = 0;
    if (func_002DCC38(arg0, arg1, arg2, arg3, arg4) != 0) {
        return func_002DCA68(0, 0xFF020301, arg2, arg3, arg4);
    }
    fp = *(void **)((u8 *)arg0 + 0xD4);
    return ((s32 (*)(s32, s32))fp)(arg0, arg1);
}
