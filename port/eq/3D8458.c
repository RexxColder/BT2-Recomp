#include "m2c_macros.h"

s32 func_003D8458(u8 *arg0) {
    s32 x = *(s32 *)(*(u8 **)0x003876A4 + 0x90);
    s32 f = *(s32 *)(arg0 + 0x3320);

    switch (x) {
    case 0:
        return f == 1;
    case 1:
        return f == 2;
    case 2:
    case 3:
        return f == 3;
    default:
        return 0;
    }
}
