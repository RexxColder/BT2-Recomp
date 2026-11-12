#include "common.h"

void func_001C1290(u8 *arg0, u8 *arg1) {
    s64 lo = *(s64 *)(arg1 + 0);
    s64 hi = *(s64 *)(arg1 + 8);
    u8 *t;

    if (arg0 != NULL) {
        t = *(u8 **)(arg0 + 0x38);
        if (t != NULL) {
            *(s64 *)(t + 0xAB0) = lo;
            *(s64 *)(t + 0xAB8) = hi;
        }
    }
}
