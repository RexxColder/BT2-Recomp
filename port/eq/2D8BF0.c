#include "common.h"

extern s32 D_003475D8 __attribute__((section(".data")));

f32 func_002D8BF0(s64 arg0) {
    s32 v = (s32)arg0;

    return ((f32)v * 1000.0f) / (f32)D_003475D8;
}
