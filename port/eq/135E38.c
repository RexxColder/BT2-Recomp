#include "common.h"

s32 func_00135E38(u8 *arg0) {
    s32 a;
    s32 b;

    if (*(s32 *)(arg0 + 8) <= 0) {
        return 0;
    }
    a = *(s32 *)(arg0 + 0);
    if (a > 0x97FF) {
        return 0;
    }
    if (a < 0x6801) {
        return 0;
    }
    b = *(s32 *)(arg0 + 4);
    if (b > 0x94FF) {
        return 0;
    }
    return b >= 0x6B01;
}
