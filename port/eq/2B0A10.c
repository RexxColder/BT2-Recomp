#include "common.h"

extern u8 *func_002B1DD0(s32 arg0);
extern void func_00312650(f32 *dst, u8 *a, u8 *b);
extern f32 func_0029DFD0(f32 *v);
extern s32 func_002ADFC8(u8 *obj);
extern s32 func_002ADFD0(u8 *obj);
extern s32 rand(void);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 atan2f(f32 y, f32 x);
extern u8 *D_003876A4;
extern s32 D_00377C88[3];
extern f32 D_00387524;
extern f32 D_00387528;
extern f32 D_0038752C;
extern f32 D_00387530;
extern f32 D_00387534;
extern f32 D_00387538;
extern f32 D_0038753C;
extern f32 D_00387540;
extern f32 D_00387544;
extern f32 D_00387548;
extern f32 D_0038754C;
extern f32 D_00387550;
extern f32 D_00387554;
extern f32 D_00387558;
extern f32 D_0038755C;
extern f32 D_00387560;

void func_002B0A10(u8 *obj) {
    f32 d[4];
    s32 tbl[3];
    f32 wrap, half, len, ang, thresh, ang2, k;
    u8 *other;
    u32 *flags = (u32 *)(obj + 0xB0);
    f32 *out = (f32 *)(obj + 0xB0);
    s32 idx;
    s32 type;
    s32 i;

    other = func_002B1DD0(0);
    wrap = D_00387524;
    if (*(s32 *)(obj + 0x10) != 3) {
        return;
    }
    idx = 0;
    if (D_003876A4 != 0) {
        idx = *(s32 *)(D_003876A4 + 0x38);
        if (idx < 0) {
            idx = 0;
        }
        if (!(idx < 3)) {
            idx = 2;
        }
    }
    half = (f32)idx * 0.5f;
    for (i = 0; i < 5; i++) {
        flags[i] = 0;
    }
    func_00312650(d, other + 0xD0, obj + 0xD0);

    if (d[0] < -wrap) {
        d[0] = d[0] + D_00387528;
    }
    if (wrap < d[0]) {
        d[0] = d[0] - D_0038752C;
    }
    if (d[2] < -wrap) {
        d[2] = d[2] + D_00387530;
    }
    if (wrap < d[2]) {
        d[2] = d[2] - D_00387534;
    }
    len = func_0029DFD0(d);
    ang = atan2f(d[0], d[2]) - *(f32 *)(obj + 0x15C);
    if (ang < D_00387538) {
        ang = ang + D_0038753C;
    }
    if (D_00387540 < ang) {
        ang = ang - D_00387544;
    }
    thresh = (half * 0.5f + 0.5f) * 2000.0f;
    *(f32 *)(obj + 0x16C) = half * D_00387548 + 0.5f;

    type = func_002ADFC8(obj);
    if (type == 2) {
        *flags |= 0x100;
        return;
    }
    if (type >= 3) {
        if (type != 3) {
            return;
        }
        *flags |= 0x100;
        if (func_002ADFD0(obj) < 0x3D) {
            return;
        }
        if (thresh < len) {
            *flags &= ~0x100;
        }
        if (__builtin_fabsf(ang) < D_00387554) {
            *flags &= ~0x100;
        }
        if (len < 300.0f) {
            for (i = 0; i < 3; i++) {
                tbl[i] = D_00377C88[i];
            }
            if (rand() % tbl[idx] == 0) {
                *flags &= ~0x100;
            }
            return;
        }
        if (!(len < 600.0f)) {
            return;
        }
        if (0.0f < ang) {
            k = D_00387558;
            ang = half * D_00387554;
        } else {
            ang = D_0038755C;
            k = D_00387560;
            ang = half * ang;
        }
        ang = ang * k;
    } else {
        if (type != 1) {
            return;
        }
        if (!(len < 1000.0f)) {
            return;
        }
        ang2 = atan2f(-d[0], -d[2]) - *(f32 *)(obj + 0x70);
        ang = ang2 + half * D_0038754C * (f32)(rand() & 0xFFFF) * D_00387550;
    }
    out[1] = sinf(ang);
    out[2] = -cosf(ang);
}
