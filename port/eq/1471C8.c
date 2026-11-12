#include "common.h"

extern void EftTexSet_Keep32(u8 *arg0, s32 arg1, s32 arg2);
extern u8 *EftWeather_GetWindPtr(void);
extern void func_003126C8(void *arg0, void *arg1);
extern void func_00145A58(void *a0, void *a1, void *a2);
extern void func_00145A30(void *a0, void *a1, void *a2);
extern void func_00312638(void *arg0, void *arg1, void *arg2);
extern void func_00312680(void *arg0, void *arg1, f32 farg0);
extern s32 rand(void);
extern u8 *D_00387758;
extern u8 *D_003876A0;
extern u64 D_0036DDF0[2];
extern f32 D_0038456C;
extern f32 D_00384570;
extern f32 D_00384574;
extern f32 D_00384578;

/* Weather particle update: jitters the first 512 position records (clamped to a box), adds
   the wind vector, then wraps the 2304 live rain records around the camera box and sets
   their fade factor. */
void func_001471C8(void) {
    u64 wind[2];
    f32 rel[4];
    f32 half[4];
    f32 full[4];
    u8 *pool;
    u8 *emit;
    u8 *rec;
    s32 i;
    f32 jitter = D_0038456C;
    f32 scale = D_00384570;
    f32 lo = D_00384574;
    f32 hi;

    EftTexSet_Keep32(D_00387758 + 0x2C000, 1, 0);
    if (*(u64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return;
    }
    emit = *(u8 **)(D_00387758 + 0x30000 - 0x3DF0);
    wind[0] = D_0036DDF0[0];
    wind[1] = D_0036DDF0[1];
    {
        u8 *w = EftWeather_GetWindPtr();
        if (w) {
            func_003126C8(wind, w);
            *(s32 *)((u8 *)wind + 0xC) = 0;
        }
    }

    pool = D_00387758;
    if (*(s32 *)(emit + 0x10) != 0) {
        rec = pool;
        for (i = 511; i >= 0; i--) {
            f32 *x = (f32 *)(rec + 0x10);
            f32 *z = (f32 *)(rec + 0x18);

            *x = *x + (f32)((rand() & 0x1FF) - 255) * jitter * scale;
            *z = *z + (f32)((rand() & 0x1FF) - 255) * jitter * scale;
            hi = D_00384578;
            if (*x < lo) {
                *x = lo;
            }
            if (hi < *x) {
                *x = hi;
            }
            if (*z < lo) {
                *z = lo;
            }
            if (hi < *z) {
                *z = hi;
            }
            func_00145A58(rec, rec, rec + 0x10);
            func_00145A58(rec, rec, wind);
            rec += 0x40;
        }
    }

    rec = D_00387758 + 0x8000;
    for (i = 2303; i >= 0; i--, rec += 0x40) {
        u8 *cam;
        f32 ratio;

        if (*(s32 *)(rec + 0x28) < 0) {
            continue;
        }
        func_00145A58(rec, rec, rec + 0x10);
        func_00312638(rec, rec, wind);
        cam = *(u8 **)(rec + 0x30);
        func_00145A30(rel, rec, cam);
        func_00312680(half, cam + 0x10, 0.5f);
        func_00312680(full, cam + 0x10, 1.0f);

        ratio = __builtin_sqrtf(__builtin_fabsf(rel[0] * rel[0] + rel[2] * rel[2])) / (half[0] * 1.5f);
        if (ratio < 1.0f) {
            *(f32 *)(rec + 0x34) = 1.0f - ratio;
        } else {
            *(s32 *)(rec + 0x34) = 0;
        }
        if (half[0] < rel[0]) {
            rel[0] = rel[0] - full[0];
        }
        if (rel[0] < -half[0]) {
            rel[0] = rel[0] + full[0];
        }
        if (half[2] < rel[2]) {
            rel[2] = rel[2] - full[2];
        }
        if (rel[2] < -half[2]) {
            rel[2] = rel[2] + full[2];
        }
        func_00145A58(rec, rel, cam);
    }
}
