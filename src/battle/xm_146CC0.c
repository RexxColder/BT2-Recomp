#include "m2c_macros.h"

extern void *gEftWeather;

// Copies three floats of the weather object (+0x220, +0x224, +0x228) into arg0 at +0, +4, +8 and sets arg0+0xC to 1.0 (only when gEftWeather exists).
void func_00146CC0(void *arg0) {
    f32 z;

    if (gEftWeather != NULL) {
        M2C_FIELD(arg0, f32 *, 0) = (f32) M2C_FIELD(gEftWeather, f32 *, 0x220);
        M2C_FIELD(arg0, f32 *, 4) = (f32) M2C_FIELD(gEftWeather, f32 *, 0x224);
        z = (f32) M2C_FIELD(gEftWeather, f32 *, 0x228);
        M2C_FIELD(arg0, f32 *, 0xC) = 1.0f;
        M2C_FIELD(arg0, f32 *, 8) = z;
    }
}
