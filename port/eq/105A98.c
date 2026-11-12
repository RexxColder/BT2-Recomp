#include "common.h"

extern s32 *D_003876B4;

s32 func_00105A98(void) {
    s32 result = 0;
    if (D_003876B4 != NULL) {
        result = *D_003876B4 == 3;
    }
    return result;
}
