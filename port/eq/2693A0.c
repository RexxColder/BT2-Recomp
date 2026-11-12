#include "common.h"

f32 func_002693A0(f32 arg0) {
    if (50.0f < arg0) {
        return 0.0f;
    }
    if (!(20.0f < arg0)) {
        return 26.0f;
    }
    return 26.0f - (((arg0 - 20.0f) / 30.0f) * 26.0f);
}
