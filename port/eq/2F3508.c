#include "common.h"

s32 func_002FE8A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002F3508(u8 *arg0) {
    s32 ret = 0;

    if (arg0 != NULL) {
        ret = func_002FE8A8(*(s32 *)(arg0 + 0x0), *(s32 *)(arg0 + 0x8),
                            *(s32 *)(arg0 + 0xC), *(s32 *)(arg0 + 0x4));
    } else {
        func_002FE8A8((s32)arg0, 0, 0, 0);
    }
    return ret;
}
