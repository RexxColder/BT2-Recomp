#include "m2c_macros.h"

extern s32 D_003475D8 __attribute__((section(".data")));

f32 func_002D8BB0(s64 arg0) {
    s32 a = (s32)arg0;

    return ((f32)a * 1000000.0f) / (f32)D_003475D8;
}
