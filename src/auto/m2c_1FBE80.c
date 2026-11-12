#include "m2c_macros.h"

void CamShake_Add(void *shake, f32 strength, f32 time);   /* extern */

/* f12/f13 (strength, time) are func_001FBE80's own params, passed through to CamShake_Add (tail call). */
void func_001FBE80(void *arg0, f32 farg0, f32 farg1) {
    if (M2C_FIELD(arg0, u8 *, 0x208) != 0) {
        CamShake_Add(arg0 + 0x1D0, farg0, farg1);
    }
}
