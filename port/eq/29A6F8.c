#include "common.h"

extern f32 D_0038724C;
extern f32 D_00387250;
void func_003126C8(f32 *dst, u8 *src);

/* 0x0029A6F8 Quat_Pack: packs a unit quaternion into 64 bits. Index of the largest |component| in bits 60+; that
 * component is dropped (sign normalized so it is positive) and the other three get 20 bits each. */
s64 Quat_Pack(u8 *src) {
    f32 q[4];
    f32 maxabs;
    f32 a;
    s32 maxi = 0;
    s32 i;
    s64 out = 0;
    s32 shift = 0;

    func_003126C8(q, src);
    maxabs = __builtin_fabsf(q[0]);
    for (i = 1; i < 4; i++) {
        a = __builtin_fabsf(q[i]);
        if (maxabs < a) {
            maxabs = a;
            maxi = i;
        }
    }
    if (q[maxi] < 0.0f) {
        q[0] = -q[0];
        q[1] = -q[1];
        q[2] = -q[2];
        q[3] = -q[3];
    }
    for (i = maxi; i < 3; i++) {
        q[i] = q[i + 1];
    }
    for (i = 0; i < 3; i++) {
        s32 v = (s32)((q[i] * D_0038724C + 0.5f) * D_00387250);
        if (v < 0) {
            v = 0;
        }
        if (v > 0xFFFFF) {
            v = 0xFFFFF;
        }
        out |= (s64)v << shift;
        shift += 20;
    }
    return out | ((s64)maxi << 60);
}
