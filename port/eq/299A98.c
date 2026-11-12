#include "common.h"

f32 atan2f(f32 y, f32 x);
f32 fabsf(f32 x);
extern f32 D_00387224;

f32 func_00299A98(f32 arg0, f32 arg1) {
    if (fabsf(arg0) < D_00387224 && fabsf(arg1) < D_00387224) {
        return 0.0f;
    }
    return atan2f(arg0, arg1);
}
