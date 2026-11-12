#include "common.h"

extern s32 func_002411A0(s32 arg0, s32 arg1);
extern s32 func_00203C58(s32 arg0, s64 arg1);

s32 func_00241718(u8 *self, s32 arg1) {
    s32 idx;
    s32 value;
    u8 *owner;

    idx = func_002411A0((s32)self, arg1);
    owner = *(u8 **)(self + 0x1530);
    value = *(s32 *)(*(u8 **)(owner + 0x980) + idx * 4 + 0x54);
    if (func_00203C58((s32)self, 0x1000000000LL)) {
        value = value / 2;
    }
    return value;
}
