#include "m2c_macros.h"

void func_001E6878(s32, f32);                         /* extern */

void func_001E7268(s32 *arg0, f32 farg0) {
    s32 temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != 0) {
        func_001E6878(temp_v0, farg0);
    }
}
