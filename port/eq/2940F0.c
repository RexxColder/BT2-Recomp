#include "common.h"

extern f32 D_00387198;
extern f32 D_0038719C;
extern void func_00312650(void *arg0, void *arg1, void *arg2);
extern f32 sceVu0InnerProduct(void *arg0, void *arg1);

/* Point / triangle squared distance (Magic Software MgcDist3DVecTri); pt = a0, tri = a1 (3 vec4),
   s/t = optional barycentric outputs. Degenerate triangle returns D_0038719C. */
f32 func_002940F0(f32 *pt, f32 *tri, f32 *s, f32 *t) {
    f32 e0[4] __attribute__((aligned(16)));
    f32 e1[4] __attribute__((aligned(16)));
    f32 diff[4] __attribute__((aligned(16)));
    f32 fA00;
    f32 fA01;
    f32 fA11;
    f32 fB0;
    f32 fB1;
    f32 fC;
    f32 fDet;
    f32 fS;
    f32 fT;
    f32 fSqrDist;

    func_00312650(e0, tri + 4, tri);
    func_00312650(e1, tri + 8, tri);
    func_00312650(diff, tri, pt);
    fA00 = sceVu0InnerProduct(e0, e0);
    fA01 = sceVu0InnerProduct(e0, e1);
    fA11 = sceVu0InnerProduct(e1, e1);
    fB0 = sceVu0InnerProduct(diff, e0);
    fB1 = sceVu0InnerProduct(diff, e1);
    fC = sceVu0InnerProduct(diff, diff);
    fDet = __builtin_fabsf(fA00 * fA11 - fA01 * fA01);
    fS = fA01 * fB1 - fA11 * fB0;
    fT = fA01 * fB0 - fA00 * fB1;
    if (__builtin_fabsf(fDet) < D_00387198) {
        return D_0038719C;
    }
    if (fS + fT <= fDet) {
        if (fS < 0.0f) {
            if (fT < 0.0f) {
                if (fB0 < 0.0f) {
                    fT = 0.0f;
                    if (-fB0 >= fA00) {
                        fS = 1.0f;
                        fSqrDist = fA00 + 2.0f * fB0 + fC;
                    } else {
                        fS = -fB0 / fA00;
                        fSqrDist = fB0 * fS + fC;
                    }
                } else {
                    fS = 0.0f;
                    if (fB1 >= 0.0f) {
                        fT = 0.0f;
                        fSqrDist = fC;
                    } else if (-fB1 >= fA11) {
                        fT = 1.0f;
                        fSqrDist = fA11 + 2.0f * fB1 + fC;
                    } else {
                        fT = -fB1 / fA11;
                        fSqrDist = fB1 * fT + fC;
                    }
                }
            } else {
                fS = 0.0f;
                if (fB1 >= 0.0f) {
                    fT = 0.0f;
                    fSqrDist = fC;
                } else if (-fB1 >= fA11) {
                    fT = 1.0f;
                    fSqrDist = fA11 + 2.0f * fB1 + fC;
                } else {
                    fT = -fB1 / fA11;
                    fSqrDist = fB1 * fT + fC;
                }
            }
        } else if (fT < 0.0f) {
            fT = 0.0f;
            if (fB0 >= 0.0f) {
                fS = 0.0f;
                fSqrDist = fC;
            } else if (-fB0 >= fA00) {
                fS = 1.0f;
                fSqrDist = fA00 + 2.0f * fB0 + fC;
            } else {
                fS = -fB0 / fA00;
                fSqrDist = fB0 * fS + fC;
            }
        } else {
            f32 fInvDet = 1.0f / fDet;

            fS *= fInvDet;
            fT *= fInvDet;
            fSqrDist = fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) + fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
        }
    } else {
        f32 fTmp0;
        f32 fTmp1;
        f32 fNumer;
        f32 fDenom;

        if (fS < 0.0f) {
            fTmp0 = fA01 + fB0;
            fTmp1 = fA11 + fB1;
            if (fTmp1 > fTmp0) {
                fNumer = fTmp1 - fTmp0;
                fDenom = fA00 - 2.0f * fA01 + fA11;
                if (fNumer >= fDenom) {
                    fS = 1.0f;
                    fT = 0.0f;
                    fSqrDist = fA00 + 2.0f * fB0 + fC;
                } else {
                    fS = fNumer / fDenom;
                    fT = 1.0f - fS;
                    fSqrDist =
                        fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) + fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
                }
            } else {
                fS = 0.0f;
                if (fTmp1 <= 0.0f) {
                    fT = 1.0f;
                    fSqrDist = fA11 + 2.0f * fB1 + fC;
                } else if (fB1 >= 0.0f) {
                    fT = 0.0f;
                    fSqrDist = fC;
                } else {
                    fT = -fB1 / fA11;
                    fSqrDist = fB1 * fT + fC;
                }
            }
        } else if (fT < 0.0f) {
            fTmp0 = fA01 + fB1;
            fTmp1 = fA00 + fB0;
            if (fTmp1 > fTmp0) {
                fNumer = fTmp1 - fTmp0;
                fDenom = fA00 - 2.0f * fA01 + fA11;
                if (fNumer >= fDenom) {
                    fT = 1.0f;
                    fS = 0.0f;
                    fSqrDist = fA11 + 2.0f * fB1 + fC;
                } else {
                    fT = fNumer / fDenom;
                    fS = 1.0f - fT;
                    fSqrDist =
                        fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) + fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
                }
            } else {
                fT = 0.0f;
                if (fTmp1 <= 0.0f) {
                    fS = 1.0f;
                    fSqrDist = fA00 + 2.0f * fB0 + fC;
                } else if (fB0 >= 0.0f) {
                    fS = 0.0f;
                    fSqrDist = fC;
                } else {
                    fS = -fB0 / fA00;
                    fSqrDist = fB0 * fS + fC;
                }
            }
        } else {
            fNumer = fA11 + fB1 - fA01 - fB0;
            if (fNumer <= 0.0f) {
                fS = 0.0f;
                fT = 1.0f;
                fSqrDist = fA11 + 2.0f * fB1 + fC;
            } else {
                fDenom = fA00 - 2.0f * fA01 + fA11;
                if (fNumer >= fDenom) {
                    fS = 1.0f;
                    fT = 0.0f;
                    fSqrDist = fA00 + 2.0f * fB0 + fC;
                } else {
                    fS = fNumer / fDenom;
                    fT = 1.0f - fS;
                    fSqrDist =
                        fS * (fA00 * fS + fA01 * fT + 2.0f * fB0) + fT * (fA01 * fS + fA11 * fT + 2.0f * fB1) + fC;
                }
            }
        }
    }
    if (s != NULL) {
        *s = fS;
    }
    if (t != NULL) {
        *t = fT;
    }
    return __builtin_fabsf(fSqrDist);
}
