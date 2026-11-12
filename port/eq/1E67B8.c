#include "common.h"

void func_001E67B8(s32 arg0, s8 arg1) {
    s32 p;

    if (arg0 != 0) {
        p = *(s32 *)(arg0 + 0x38);
        if ((*(s64 *)p & 5) == 1) {
            *(s8 *)(p + 4) = arg1;
        }
    }
}
