#include "common.h"

u8 *func_00101A88(s32 arg0);

s32 func_0010CDD8(s32 arg0, s32 arg1) {
    return *(s32 *)(func_00101A88(arg0) + arg1 * 88 + 0x54);
}
