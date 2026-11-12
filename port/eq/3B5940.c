#include "m2c_macros.h"


#define M2C_PI_F 3.14159265f
#define M2C_TWO_PI_F 6.28318548f

f32 func_003B5940(f32 x) {
    f32 r;
    f32 t;
    s32 q;
    f32 f;

    r = x;
    if (M2C_PI_F <= x) {
        t = x - M2C_PI_F;
        q = (s32)(t / M2C_TWO_PI_F); /* cvt.w.s: trunca */
        if (q < 0) {
            q = -q;
        }
        f = (f32)q * M2C_TWO_PI_F + M2C_TWO_PI_F;
        r = x - f;
    } else if (x <= -M2C_PI_F) {
        t = x + M2C_PI_F;
        q = (s32)(t / M2C_TWO_PI_F); /* cvt.w.s: trunca */
        if (q < 0) {
            q = -q;
        }
        f = (f32)q * M2C_TWO_PI_F + M2C_TWO_PI_F;
        r = x + f;
    }
    return r;
}
