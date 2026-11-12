#include "common.h"

void func_00312680(void *arg0, void *arg1, f32 farg0);
f32 sceVu0InnerProduct(u8 *arg0, u8 *arg1);
f32 Mathf_Acos(f32 farg0);

/* 0x00217E58: builds four 3-vectors (x, y, 0) from float pairs of arg0 ([2],[3]), ([11],[12]), ([4],[5]) and
 * ([13],[14]). Pairs 0/1 are normalized when both lengths exceed 0.5, and their dot product gives an angle
 * (acos, clamped to 1, only for a positive dot). Pairs 2/3 do the same. Returns the largest of 0 and the two angles. */
f32 func_00217E58(f32 *arg0) {
    f32 vec[16];
    f32 len0;
    f32 len1;
    f32 len2;
    f32 len3;
    f32 dot;
    f32 angleA = 0.0f;
    f32 angleB = 0.0f;
    f32 best = 0.0f;

    vec[0] = arg0[2];
    vec[1] = arg0[3];
    vec[2] = 0.0f;
    vec[4] = arg0[11];
    vec[5] = arg0[12];
    vec[6] = 0.0f;
    vec[8] = arg0[4];
    vec[9] = arg0[5];
    vec[10] = 0.0f;
    vec[12] = arg0[13];
    vec[13] = arg0[14];
    vec[14] = 0.0f;

    len0 = __builtin_sqrtf(arg0[2] * arg0[2] + arg0[3] * arg0[3]);
    len1 = __builtin_sqrtf(vec[4] * vec[4] + vec[5] * vec[5]);
    len2 = __builtin_sqrtf(vec[8] * vec[8] + vec[9] * vec[9]);
    len3 = __builtin_sqrtf(vec[12] * vec[12] + vec[13] * vec[13]);

    if (0.5f < len0 && 0.5f < len1) {
        func_00312680(&vec[0], &vec[0], 1.0f / len0);
        func_00312680(&vec[4], &vec[4], 1.0f / len1);
        dot = sceVu0InnerProduct((u8 *)&vec[0], (u8 *)&vec[4]);
        if (0.0f < dot) {
            if (1.0f < dot) {
                dot = 1.0f;
            }
            angleA = Mathf_Acos(dot);
        }
    }

    if (0.5f < len2 && 0.5f < len3) {
        func_00312680(&vec[8], &vec[8], 1.0f / len2);
        func_00312680(&vec[12], &vec[12], 1.0f / len3);
        dot = sceVu0InnerProduct((u8 *)&vec[8], (u8 *)&vec[12]);
        if (0.0f < dot) {
            if (1.0f < dot) {
                dot = 1.0f;
            }
            angleB = Mathf_Acos(dot);
        }
    }

    if (best < angleA) {
        best = angleA;
    }
    if (best < angleB) {
        best = angleB;
    }
    return best;
}
