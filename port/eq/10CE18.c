#include "common.h"

s32 rand(void);
extern f32 D_00383E28;
extern f32 D_00383E2C;

void func_0010CE18(void *arg0) {
    f32 *p;
    f32 sx;
    f32 sy;
    f32 f0;
    f32 t;

    p = (f32 *)arg0;
    if (p[0] > 0.0f) {
        sx = (rand() & 1) ? -1.0f : 1.0f;
        sy = (rand() & 1) ? -1.0f : 1.0f;
        p[1] = (((f32)rand() / D_00383E28) * 0.5f + 0.5f) * 20.0f * p[0] * sx;
        f0 = (((f32)rand() / D_00383E28) * 0.5f + 0.5f) * 20.0f * p[0] * sy;
        p[2] = f0;
        t = p[1];
        if (5.0f < t) {
            p[1] = 5.0f;
            t = 5.0f;
        }
        if (t < -5.0f) {
            p[1] = -5.0f;
        }
        t = p[2];
        if (5.0f < t) {
            p[2] = 5.0f;
            t = 5.0f;
        }
        if (t < -5.0f) {
            p[2] = -5.0f;
        }
    } else {
        p[2] = 0.0f;
        p[1] = 0.0f;
    }
    f0 = p[0] - D_00383E2C;
    p[0] = f0;
    if (f0 < 0.0f) {
        p[0] = 0.0f;
    }
}
