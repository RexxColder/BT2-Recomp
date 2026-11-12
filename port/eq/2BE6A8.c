#include "common.h"

s32 func_002C0250(s32 arg0, s32 arg1, s32 arg2);

s32 func_002BE6A8(u8 *arg0, s32 arg1) {
    return func_002C0250((s32)arg0, *(s32 *)(arg0 + 0x200C), arg1);
}
