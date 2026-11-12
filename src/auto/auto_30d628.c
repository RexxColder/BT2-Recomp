#include "common.h"

/* atan2f */
extern f32 __ieee754_atan2f(f32 y, f32 x);
f32 atan2f(f32 y, f32 x) { return __ieee754_atan2f(y, x); }
