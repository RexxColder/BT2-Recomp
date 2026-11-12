#include "common.h"

extern void ColSeg_NearestOnLine(f32 *arg0, f32 *arg1, f32 *arg2, s32 arg3, f32 farg0, f32 *arg4, f32 *arg5);

static f32 Clamp01(f32 v) {
    f32 hi = 1.0f;
    if (v < hi) {
        hi = 0.0f;
        if (!(v < hi)) {
            hi = v;
        }
    }
    return hi;
}

/* Nearest points of two segments when a parameter s or t of the infinite-line solution fell outside [0, 1]:
   clamp it, rebuild that point and re-solve the other one. */
void func_00295298(f32 *a, f32 *la, f32 *b, f32 *lb, f32 epsSq, f32 s, f32 t, f32 *onA, f32 *onB) {
    f32 sv = s;
    f32 tv = t;

    if ((sv < 0.0f || 1.0f < sv) && (tv < 0.0f || 1.0f < tv)) {
        sv = Clamp01(sv);
        onA[0] = a[0] + sv * la[0];
        onA[1] = a[1] + sv * la[1];
        onA[2] = a[2] + sv * la[2];
        ColSeg_NearestOnLine(b, lb, onA, 1, epsSq, onB, &tv);
        if (tv < 0.0f || 1.0f < tv) {
            tv = Clamp01(tv);
            onB[0] = b[0] + tv * lb[0];
            onB[1] = b[1] + tv * lb[1];
            onB[2] = b[2] + tv * lb[2];
            ColSeg_NearestOnLine(a, la, onB, 0, epsSq, onA, &sv);
            ColSeg_NearestOnLine(b, lb, onA, 0, epsSq, onB, &tv);
        }
    } else if (sv < 0.0f || 1.0f < sv) {
        sv = Clamp01(sv);
        onA[0] = a[0] + sv * la[0];
        onA[1] = a[1] + sv * la[1];
        onA[2] = a[2] + sv * la[2];
        ColSeg_NearestOnLine(b, lb, onA, 0, epsSq, onB, &tv);
    } else if (tv < 0.0f || 1.0f < tv) {
        tv = Clamp01(tv);
        onB[0] = b[0] + tv * lb[0];
        onB[1] = b[1] + tv * lb[1];
        onB[2] = b[2] + tv * lb[2];
        ColSeg_NearestOnLine(a, la, onB, 0, epsSq, onA, &sv);
    }
}
