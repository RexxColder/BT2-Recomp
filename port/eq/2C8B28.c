#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);
s32 func_002DD200(s32 arg0, s64 arg1, s32 arg2);
s32 func_002DD6A8(s32 arg0, s32 arg1, s32 arg2);

s32 func_002C8B28(s32 arg0, s32 arg1, s32 arg2) {
    s32 v1;

    if (func_002D07B0(arg0, 7) != 0) {
        return 0;
    }
    if (arg1 == 3) {
        v1 = func_002DD200(*(s32 *)(arg2 + 0), *(s32 *)(arg2 + 4),
                           *(s32 *)(arg0 + 0x90C + 8) * *(s32 *)(arg0 + 0x90C + 0xC));
        if (v1 != 0) {
            *(s32 *)(arg0 + 0x950 + 0x10) = *(s32 *)(arg0 + 0x950 + 0x10) + 1;
        }
        return v1;
    }
    if (arg1 == 2) {
        v1 = func_002DD6A8(*(s32 *)(arg2 + 0), *(s32 *)(arg2 + 4),
                           *(s32 *)(arg0 + 0x90C + 8) * *(s32 *)(arg0 + 0x90C + 0xC));
        if (v1 != 0) {
            *(s32 *)(arg0 + 0x950 + 0x14) = *(s32 *)(arg0 + 0x950 + 0x14) + 1;
        }
        return v1;
    }
    return 0;
}
