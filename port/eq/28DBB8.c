#include "common.h"

s32 Col_NearEq(f32 a, f32 b, f32 eps) {
    if (__builtin_fabsf(a - b) <= eps) {
        return 1;
    }
    return 0;
}
