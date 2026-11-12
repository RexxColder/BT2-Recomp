#include "common.h"

extern u8 *D_00387A30;
extern u8 *D_003876A0;
extern u8 *gBtlCam;
extern f32 D_00386DB0;
extern f32 D_00386DB4;
extern f32 D_00386DB8;
extern f32 D_00386DBC;

void *memset(void *s, s32 c, u32 n);
void CamShake_Tick(void *a0);
void DemoCam_SetTime(f32 f12);
void DemoCam_Stop(f32 f12);
void func_00209BC8(void *a0, void *a1);
s32 func_0020B328(void *a0);
void func_0025A188(void *a0, f32 f12);
void func_0025AA98(void *a0);
f32 func_0025AAD0(void);
f32 func_0025AAF0(void *a0, s32 a1);
void func_0025B5E8(void *a0, void *a1);
void func_0025BDD0(void *a0, void *a1, void *a2);
void func_0025C2D8(void *a0, void *a1, void *a2);
s32 func_0025C458(void *a0, void *a1, void *a2, void *a3, s32 t0);
void *func_00269A40(void *a0, s32 a1);
void func_0029D5C8(void *a0);
void func_003126C8(void *a0, void *a1);
void sceVu0UnitMatrix(void *m);
void sceVu0MulMatrix(void *d, void *a, void *b);
void sceVu0InversMatrix(void *d, void *s);
void sceVu0RotMatrixX(void *d, void *s, f32 angle);
void sceVu0RotMatrixY(void *d, void *s, f32 angle);
void sceVu0RotMatrixZ(void *d, void *s, f32 angle);

s32 func_0025A4E0(void) {
    u8 sp[0x140] __attribute__((aligned(16)));
    u8 *D;
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s4;
    u8 *s5;
    u8 *ptr;
    u8 *v958;
    f32 f20;
    f32 f12;
    f32 f3;
    f32 *vp;
    s32 k;
    s32 r;
    s64 flags;

    D = D_00387A30;
    if (D[0x31C] != 0) {
        /* four 4x4 identity-ish vectors with w = 1 */
        memset(sp + 0x00, 0, 0x10);
        *(f32 *)(sp + 0x0C) = 1.0f;
        memset(sp + 0x10, 0, 0x10);
        *(f32 *)(sp + 0x1C) = 1.0f;
        memset(sp + 0x20, 0, 0x10);
        *(f32 *)(sp + 0x2C) = 1.0f;
        memset(sp + 0x30, 0, 0x10);
        *(f32 *)(sp + 0x3C) = 1.0f;
        func_003126C8(sp + 0x20, D + 0x2C0);
        func_003126C8(sp + 0x30, D + 0x2D0);
        func_0025C2D8(D + 0x2FC, sp + 0x00, sp + 0x10);
        *(f32 *)(sp + 0x20) = *(f32 *)(sp + 0x20) + *(f32 *)(sp + 0x00);
        *(f32 *)(sp + 0x24) = *(f32 *)(sp + 0x24) + *(f32 *)(sp + 0x04);
        *(f32 *)(sp + 0x28) = *(f32 *)(sp + 0x28) + *(f32 *)(sp + 0x08);
        *(f32 *)(sp + 0x30) = *(f32 *)(sp + 0x30) + *(f32 *)(sp + 0x10);
        *(f32 *)(sp + 0x34) = *(f32 *)(sp + 0x34) + *(f32 *)(sp + 0x14);
        *(f32 *)(sp + 0x38) = *(f32 *)(sp + 0x38) + *(f32 *)(sp + 0x18);
        CamShake_Tick(D + 0x2FC);
        func_0025BDD0(D, sp + 0x20, sp + 0x30);
        func_0025B5E8(D, sp + 0x20);
        return 0;
    }

    if (*(s32 *)(D + 0x2B0) == 0) {
        return 1;
    }

    if ((*(s32 *)(D + 0x2F8) & 4) && !(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        f20 = func_0025AAF0(D, 0) + 2.0f;
        f12 = f20;
        if (func_0025AAD0() < f20) {
            if (*(s32 *)(D + 0x2F8) & 8) {
                DemoCam_Stop(f20);
            }
            f12 = func_0025AAD0();
        }
        DemoCam_SetTime(f12);
    }

    ptr = *(u8 **)(D + 0x2F0);
    if (ptr != NULL) {
        func_0025AA98(func_00269A40(ptr, 0));
    } else {
        ptr = *(u8 **)(D + 0x2F4);
        if (ptr != NULL) {
            func_0025AA98(ptr + 0xA00);
        }
    }
    f12 = *(f32 *)(D + 0x2E0);

    s1 = D + 0x290;
    func_0025A188(s1, f12);

    /* copy xyz of the camera vector into sp+0xD0, w = 0 */
    *(f32 *)(sp + 0xD0) = *(f32 *)(s1 + 0x0C);
    *(f32 *)(sp + 0xD4) = *(f32 *)(s1 + 0x10);
    *(f32 *)(sp + 0xD8) = *(f32 *)(s1 + 0x14);
    *(s32 *)(sp + 0xDC) = 0;
    *(s64 *)(sp + 0xC0) = *(s64 *)(sp + 0xD0);
    *(s64 *)(sp + 0xC8) = *(s64 *)(sp + 0xD8);
    s0 = sp + 0xD0;
    memset(s0, 0, 0x10);
    *(f32 *)(sp + 0xDC) = 1.0f;
    func_0025C2D8(D + 0x2FC, s0, sp + 0xE0);
    *(f32 *)(sp + 0xC0) = *(f32 *)(sp + 0xC0) + *(f32 *)(sp + 0xE0);
    *(f32 *)(sp + 0xC4) = *(f32 *)(sp + 0xC4) + *(f32 *)(sp + 0xE4);
    *(f32 *)(sp + 0xC8) = *(f32 *)(sp + 0xC8) + *(f32 *)(sp + 0xE8);
    CamShake_Tick(D + 0x2FC);

    /* wrap the three angles: three passes of the loop */
    vp = (f32 *)(sp + 0xC0);
    for (k = 0; k < 3; k++) {
        f32 e = vp[k];
        if (D_00386DB0 < e) {
            e = e - D_00386DB4;
            vp[k] = e;
        }
        if (e < D_00386DB8) {
            vp[k] = e + D_00386DB4;
        }
    }

    sceVu0UnitMatrix(D);
    sceVu0UnitMatrix(sp + 0x80);
    sceVu0RotMatrixX(sp + 0x80, sp + 0x80, *(f32 *)(sp + 0xC0));
    sceVu0MulMatrix(D, sp + 0x80, D);
    sceVu0UnitMatrix(sp + 0x80);
    sceVu0RotMatrixY(sp + 0x80, sp + 0x80, *(f32 *)(sp + 0xC4));
    sceVu0MulMatrix(D, sp + 0x80, D);
    sceVu0UnitMatrix(sp + 0x80);
    sceVu0RotMatrixZ(sp + 0x80, sp + 0x80, *(f32 *)(sp + 0xC8));
    sceVu0MulMatrix(D, sp + 0x80, D);

    /* object for the tail: first non-null of 2F0 / 2F4 */
    s0 = *(u8 **)(D + 0x2F0);
    if (s0 == NULL) {
        s0 = *(u8 **)(D + 0x2F4);
    }
    if (s0 != NULL && func_0020B328(*(void **)s0) != 0 && D[0x31D] != 0) {
        v958 = *(u8 **)(s0 + 0x958);
        f3 = *(f32 *)(v958 + 0x40) / D_00386DBC;
        *(f32 *)(D + 0x30) = *(f32 *)(s1 + 0x0) + *(f32 *)(sp + 0xD0);
        *(f32 *)(D + 0x34) = *(f32 *)(s1 + 0x4) * f3 + *(f32 *)(sp + 0xD4);
        *(f32 *)(D + 0x38) = *(f32 *)(s1 + 0x8) + *(f32 *)(sp + 0xD8);
    } else {
        *(f32 *)(D + 0x30) = *(f32 *)(s1 + 0x0) + *(f32 *)(sp + 0xD0);
        *(f32 *)(D + 0x34) = *(f32 *)(s1 + 0x4) + *(f32 *)(sp + 0xD4);
        *(f32 *)(D + 0x38) = *(f32 *)(s1 + 0x8) + *(f32 *)(sp + 0xD8);
    }

    sceVu0MulMatrix(D, D + 0x250, D);
    sceVu0InversMatrix(D, D);
    func_0029D5C8(D);
    s4 = sp + 0x40;
    sceVu0InversMatrix(s4, D);

    if (*(u8 **)(D + 0x2F0) != NULL || *(u8 **)(D + 0x2F4) != NULL) {
        flags = *(s64 *)(D_003876A0 + 0x4D8);
        if (!(flags & 0x2000) && (flags & 3)) {
            s2 = sp + 0xF0;
            s5 = sp + 0x70;
            func_003126C8(s2, s5);
            ptr = *(u8 **)(D + 0x2F0);
            if (ptr != NULL) {
                func_00209BC8(*(void **)ptr, sp + 0x100);
            } else {
                func_00209BC8(*(void **)(*(u8 **)(D + 0x2F4)), sp + 0x100);
            }
            r = func_0025C458(sp + 0x110, s2, sp + 0x100, sp + 0x120, 0);
            if (r != 0) {
                *(f32 *)(gBtlCam + 0x2C4) = 1.0f;
                *(f32 *)(gBtlCam + 0x5C4) = 1.0f;
                func_003126C8(s5, sp + 0x110);
                sceVu0InversMatrix(D, s4);
                func_0029D5C8(D);
            } else {
                *(f32 *)(gBtlCam + 0x2C4) = 1.0f;
                *(f32 *)(gBtlCam + 0x5C4) = 1.0f;
            }
        }
    }

    s5 = sp + 0x70;
    func_0025B5E8(D, s5);
    return 0;
}
