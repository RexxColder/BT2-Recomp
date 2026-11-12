#include "common.h"

extern f32 D_00386D2C;

f32 func_00241F50(u8 *arg0, s32 arg1) {
    u8 *p = *(u8 **)(*(u8 **)(arg0 + 0x1530) + 0x984) + ((arg1 != 0) * 4);
    return *(f32 *)(p + 0x80) * 10.0f * D_00386D2C;
}
