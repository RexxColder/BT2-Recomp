#include "common.h"

extern s32 func_001F97F8();
extern s32 func_00203C58(s32 arg0, s64 arg1);

s32 func_0023FAB8(u8 *self) {
    u8 *owner = *(u8 **)(self + 0x1530);
    s32 value = *(s32 *)(*(u8 **)(owner + 0x958) + 0x88) / 30;

    value += func_001F97F8((s32)self, (s32)owner);
    if (func_00203C58((s32)self, 0x40000000)) {
        value = value * 2;
    }
    return value;
}
