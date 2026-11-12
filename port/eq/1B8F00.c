#include "common.h"

void func_001B8F00(f32 *arg0, f32 farg0) {
    f32 *p = arg0;
    s32 i;

    for (i = 0; i < 6; i++) {
        p[i] = p[i] * farg0;
    }
}
