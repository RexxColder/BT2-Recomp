#include "common.h"

extern f32 cosf(f32 arg0);
extern void func_003126C8(void *arg0, void *arg1);
extern f32 D_00387274;
extern f32 D_00387278;
extern f32 D_0038727C;
extern f32 D_00387280;

/* Unpacks a 32-bit packed unit vector (11-bit z, 18-bit index, 3 sign bits) into x/y/z and
   hands it to func_003126C8. */
void func_0029AC88(void *dst, u32 packed) {
    f32 out[4];
    f32 v[4];
    u32 signs = packed >> 29;
    u32 idx = (packed >> 11) & 0x3FFFF;
    f32 z = (f32)(packed & 0x7FF) * D_00387274;
    f32 zz = 1.0f - z * z;
    s32 root = (s32)__builtin_sqrtf(__builtin_fabsf((f32)idx + 0.5f));
    s32 rem = (s32)idx - root * root;
    f32 a = (f32)(511 - root) * D_00387278 * D_0038727C;
    f32 b = (f32)rem * (1.0f / (f32)(root * 2)) * D_00387280;
    f32 ca;
    f32 cb;
    f32 sa;
    f32 scale;
    s32 i;

    ca = cosf(a);
    sa = __builtin_sqrtf(__builtin_fabsf(1.0f - ca * ca));
    cb = cosf(b);
    v[0] = cb * ca;
    v[1] = sa;
    v[2] = __builtin_sqrtf(__builtin_fabsf(1.0f - cb * cb)) * ca;
    for (i = 0; i < 3; i++) {
        if (signs & (1 << i)) {
            v[i] = -v[i];
        }
    }
    scale = __builtin_sqrtf(__builtin_fabsf(1.0f - zz * zz));
    out[2] = v[2] * scale;
    out[0] = v[0] * scale;
    out[1] = v[1] * scale;
    out[3] = zz; /* sp+0xC keeps the spilled zz = 1 - z*z; func_003126C8 copies all 16 bytes */
    func_003126C8(dst, out);
}
