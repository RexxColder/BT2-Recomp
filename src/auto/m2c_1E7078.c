#include "m2c_macros.h"

M2C_UNK func_001E67E0(s32);                         /* extern */

void FlashShapePool_Term(s32 *arg0) {
    s32 temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != 0) {
        func_001E67E0(temp_v0);
        *arg0 = 0;
    }
}
