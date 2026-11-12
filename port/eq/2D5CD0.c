#include "common.h"

s32 func_002D5CD0(u8 *arg0, u8 *arg1) {
    s32 a = *(s32 *)(arg0 + 4);

    if (a == 0x51) {
        return 4;
    }
    if (a == 0x61) {
        return 5;
    }
    return (*(s32 *)(arg1 + 0x94) ^ 0x51) != 0 ? 5 : 4;
}
