#include "common.h"

s32 func_002F3280(s32 arg0);

s32 func_002ECFA8(u8 *arg0) {
    s32 v1;

    if (arg0 != NULL) {
        v1 = *(s32 *)(arg0 + 4);
        if (v1 != 0) {
            return func_002F3280(v1);
        }
    }
    return 0;
}
