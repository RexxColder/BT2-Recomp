#include "common.h"

s32 func_002D2268(s32 arg0, s32 arg1, s32 arg2);

s32 func_002D2230(s32 arg0, void *arg1) {
    if (arg1 != NULL) {
        return func_002D2268(arg0, *(s32 *)((u8 *)arg1 + 0x14), *(s32 *)((u8 *)arg1 + 0x18));
    }
    return 0;
}
