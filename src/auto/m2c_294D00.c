#include "m2c_macros.h"

f32 ColB_Vec3Dist(void *, s32);                     /* extern */
M2C_UNK ColSeg_GetMidpoint3();                      /* extern */

void ColCapsule_GetBoundSphere(void *arg0, void *arg1) {
    f32 temp_f0;

    ColSeg_GetMidpoint3(arg0, arg1);
    temp_f0 = (ColB_Vec3Dist(arg1, arg1 + 0x10) * 0.5f) + M2C_FIELD(arg1, f32 *, 0x20);
    M2C_FIELD(arg0, f32 *, 0x10) = temp_f0;
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) (temp_f0 * temp_f0);
}
