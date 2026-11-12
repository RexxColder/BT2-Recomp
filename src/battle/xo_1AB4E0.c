#include "m2c_macros.h"

s32 FlashShapePool_Term(s32);                      /* extern */
void func_001AA9D8();                           /* extern */

/* Calls func_001AA9D8, then FlashShapePool_Term on the pool at +0xE8 of the object at +0x38 of arg0. */
void func_001AB4E0(void *arg0) {
    s32 temp_s0;
    s32 temp_v0;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x38);
    func_001AA9D8(arg0);
    temp_v0 = FlashShapePool_Term(temp_s0 + 0xE8);
    temp_s0 = temp_v0; /* keeps the call non-tail (original has ra restore after it) */
}
