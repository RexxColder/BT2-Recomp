#include "m2c_macros.h"

void func_001E68E8(s32, s32, f32, f32, f32, f32);   /* extern */

/* a1 and f12..f15 pass through to the tail-called func_001E68E8. */
void func_001E7298(s32 *arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    s32 temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != 0) {
        func_001E68E8(temp_v0, arg1, farg0, farg1, farg2, farg3);
    }
}
