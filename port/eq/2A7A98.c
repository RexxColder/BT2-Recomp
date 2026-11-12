#include "common.h"

s32 Gsc_GetInt(void);
s32 func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_002A7A98(s32 arg0) {
    if (arg0 == 0) {
        func_00297FE0(1, Gsc_GetInt(), 0x40, 0x40, 0);
    }
    return 1;
}
