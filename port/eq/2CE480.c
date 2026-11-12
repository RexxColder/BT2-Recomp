#include "common.h"

extern s32 func_002D07B0(s32 arg0, s32 arg1);

s32 func_002CE480(u8 *self, s32 delta, s32 arg2) {
    s32 *counter = (s32 *)(self + 0x950);
    s32 (*handler)(s32, s32, s32 *);

    counter[1] = counter[1] + delta;
    handler = (s32 (*)(s32, s32, s32 *))func_002D07B0((s32)self, 0x25);
    if (handler) {
        return handler((s32)self, arg2, counter);
    }
    return 0;
}
