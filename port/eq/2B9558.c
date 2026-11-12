#include "common.h"

s32 func_002B95A8(s32 arg0, s32 arg1);
s32 func_002D8300(s32 arg0, s32 arg1);

s32 func_002B9558(s32 arg0, u8 *arg1) {
    s32 r = func_002B95A8(arg0, *(s32 *)(arg1 + 0x30));
    s32 c;

    if (*(s32 *)(arg1 + 0x88) == 0) {
        return r == 1;
    }
    c = func_002D8300(*(s32 *)(arg1 + 0x88), *(s32 *)(arg1 + 0x8C));
    return c == 1;
}
