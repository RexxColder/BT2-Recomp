#include "common.h"

/* 0x00212A18 BtlChar_SetVibration (BT3 name, fuzzy): power (f12) capped at 1.0; vib = arg0 + 0x13C; if vib->time <= 0
 * or vib->power < power, vib->power = power and vib->time = truncates toward zero(seconds (f13) * 30). */
void BtlChar_SetVibration(u8 *arg0, f32 farg0, f32 farg1) {
    u8 *vib = arg0 + 0x13C;
    f32 power = farg0;
    f32 x;
    s32 t;

    if (1.0f < power) {
        power = 1.0f;
    }
    if (*(s32 *)(vib + 0x4) <= 0 || *(f32 *)vib < power) {
        *(f32 *)vib = power;
        x = farg1 * 30.0f;
        t = (s32)x;
        *(s32 *)(vib + 0x4) = t;
    }
}
