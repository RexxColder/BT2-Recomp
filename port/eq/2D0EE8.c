#include "common.h"

s32 func_002D0EE8(u8 *arg0, s32 arg1) {
    s32 a = *(s32 *)(arg0 + 0x294);
    s32 hi1 = a + *(s32 *)(arg0 + 0x298);
    s32 hi2 = a + *(s32 *)(arg0 + 0x29C);

    if (arg1 >= hi1) {
        return (arg1 < hi2) ? hi2 : 0x7FFFFFFF;
    }
    return hi1;
}
