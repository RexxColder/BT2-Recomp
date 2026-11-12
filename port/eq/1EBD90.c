#include "common.h"

s32 func_001EBD90(u8 *arg0, s16 arg1) {
    s32 v1 = arg1;

    if (v1 >= 0 && v1 < *(s16 *)(arg0 + 6)) {
        return *(s32 *)(*(u8 **)(arg0 + 0) + v1 * 4);
    }
    return 0;
}
