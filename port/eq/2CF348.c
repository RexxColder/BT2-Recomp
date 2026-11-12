#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002CF3D8(s32 arg0, s32 arg1, s32 arg2);

s32 func_002CF348(u8 *arg0, s32 arg1, s64 *arg2, s32 *arg3) {
    u8 *a0;
    s32 r;

    *arg3 = 0;
    if (*arg2 >= 0) {
        a0 = arg0 + arg1 * 0x74;
        if (*(s32 *)(a0 + 0x1348) != 0) {
            r = func_002CF3D8((s32)(a0 + 0x1348), (s32)arg2, (s32)arg3);
            if (r == -1) {
                return func_002C2FF0((s32)arg0, (s32)0xFF000421);
            }
            return 0;
        }
    }
    return 0;
}
