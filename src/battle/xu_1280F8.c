#include "common.h"
#include "m2c_macros.h"

void EftHit_SetRadiusA(s32 arg0, f32 farg0);
void EftHit_SetRadiusB(s32 arg0, f32 farg0);

/* If the object at +0x64 has word 0x153 at the word its +0x20 points to, sets both radii of arg0 to 9.0f.
   Returns 0.0f in both cases (f0 is zeroed on every path). */
f32 func_001280F8(s32 arg0) {
    u8 *t = *(u8 **)(arg0 + 0x64);

    if (t != NULL && *(s32 *)*(u8 **)(t + 0x20) == 0x153) {
        f32 r = M2C_BITWISE(f32, 0x41100000);
        EftHit_SetRadiusA(arg0, r);
        EftHit_SetRadiusB(arg0, r);
    }
    return M2C_BITWISE(f32, 0);
}
