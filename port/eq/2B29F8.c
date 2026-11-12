#include "common.h"

s32 *func_002B29F8(s32 *arg0, u32 arg1) {
    s32 *result = NULL;
    if (arg1 >= 0x8C) {
        result = arg0;
        *arg0 = 1;
    }
    return result;
}
