#include "common.h"

s32 func_002CB288(s32 arg0, s32 arg1) {
    s32 end = ((*(s32 *)((u8 *)arg0 + 8) * 0x10) + *(s32 *)((u8 *)arg0 + 4) + 0x10) & 0x0FFFFFFF;
    s32 v;

    if (arg1 == end) {
        return 0;
    }
    v = arg1 - *(s32 *)((u8 *)arg0 + 0);
    return ((v < 0) ? (v + 0x7FF) : v) >> 11;
}
