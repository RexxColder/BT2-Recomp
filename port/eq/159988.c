#include "common.h"

extern f32 D_003846C4;
extern f32 D_003846C8;

u8 *func_0020B3D0(u8 *a0);
u8 *func_00208DE8(u8 *a0, void *a1, s32 a2);
void func_00129B58(void *a0, void *a1, void *a2);
f32 func_00129CD8(void *a0, void *a1);
void func_00129C50(void *a0, void *a1, void *a2);
void Vec4_Set(void *a0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Mtx_StoreIdentity(void *a0);
void Mtx_RotateX(void *a0, void *a1, f32 farg0);
void Mtx_RotateY(void *a0, void *a1, f32 farg0);
void Vec3_Add(void *a0, void *a1, void *a2);
void Vec3_Normalize(void *a0, void *a1);
f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
f32 sqrtf(f32 farg0);
f32 fabsf(f32 farg0);

/* 0x00159988: per-frame orientation update of object arg0 (through its sub-struct at +0x38).
 * sqrt.s (EE) takes |x|. The length of a vector pair (+50, clamped at 800) is stored in 0xAA0;
 * a matrix from two angles (0x20/0x24/0x28) and a vector (+0x40 / +0x80) is rebuilt; 0xAA4 is
 * advanced by 0xAA8 and wrapped by D_003846C8 above D_003846C4. */
void func_00159988(u8 *arg0) {
    u8 *t;
    u8 *u;
    u8 *s2;
    f32 m[16];
    f32 n[16];
    f32 a[4];
    f32 b[4];
    f32 d;
    f32 tmp;
    f32 f20;
    f32 f21;

    t = *(u8 **)(arg0 + 0x38);
    u = *(u8 **)(t + 0xA0);
    s2 = func_0020B3D0(*(u8 **)u);
    func_00208DE8(*(u8 **)u, a, 3);
    func_00208DE8(s2, b, 3);
    func_00129B58(a, b, a);
    d = func_00129CD8(a, a);

    tmp = sqrtf(fabsf(d)) + 50.0f;
    *(f32 *)(t + 0xAA0) = tmp;
    if (800.0f < tmp) {
        *(f32 *)(t + 0xAA0) = 800.0f;
    }
    Vec4_Set(t + 0x70, 0.0f, 0.0f, *(f32 *)(t + 0xAA0), 1.0f);

    Mtx_StoreIdentity(m);
    Mtx_RotateY(m, m, *(f32 *)(t + 0xAA4));
    func_00129C50(t + 0x70, m, t + 0x70);

    f20 = Mathf_Asin(-*(f32 *)(t + 0x24));
    f21 = atan2f(*(f32 *)(t + 0x20), *(f32 *)(t + 0x28));
    Mtx_RotateX(n, m, f20);
    Mtx_RotateY(n, n, f21);
    func_00129C50(t + 0x70, n, t + 0x70);

    if ((*(s32 *)t & 0x80) != 0) {
        Vec3_Normalize(t + 0x80, t + 0x70);
    } else {
        Vec3_Add(t + 0x80, t + 0x70, t + 0x40);
        *(s32 *)t = *(s32 *)t | 0x80;
    }
    Vec3_Add(t + 0x70, t + 0x70, t + 0x40);

    tmp = *(f32 *)(t + 0xAA4) + *(f32 *)(t + 0xAA8);
    *(f32 *)(t + 0xAA4) = tmp;
    if (D_003846C4 < tmp) {
        *(f32 *)(t + 0xAA4) = tmp - D_003846C8;
    }
}
