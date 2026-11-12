#include "common.h"

s32 func_2B8938(s32);

s32 func_003B50F8(u8 *arg0) {
    if (arg0 != NULL) {
        return func_2B8938(*(s32 *)(arg0 + 0xC0));
    }
    return 0;
}
