#include "common.h"
#include "m2c_macros.h"

extern void *gBtlCam;
extern void *gOrbitCam;
extern u8 D_003B0C2C[] __attribute__((section(".data")));
extern f32 D_00386E38;
extern f32 D_00386E3C;
extern f32 D_00386E40;
extern f32 D_00386E44;
extern f32 D_00386E48;
extern f32 D_00386E4C;
extern f32 D_00386E50;
extern f32 D_00386E54;
extern f32 D_00386E58;
extern f32 D_00386E5C;
extern f32 D_00386E60;
extern f32 D_00386E64;
extern f32 D_00386E68;
extern f32 D_00386E6C;
extern f32 D_00386E70;

f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
f32 func_0028C610(s32 arg0, s32 arg1, s32 arg2);
void sceVu0InversMatrix(void *dst, void *src);
void func_00312680(f32 farg0, void *dst, void *src);
void func_00312638(void *dst, void *src, void *extra);
void func_00312650(void *a, void *b, void *c);
void func_0025BDD0(void *a, void *b, void *c);
void func_003126C8(void *a, void *b);

void func_0025C798(s32 arg0) {
    u8 sp[0x60];
    u8 *var_s1;
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    f32 temp_f23;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f1;
    f32 var_f1_2;

    if (gBtlCam != NULL) {
        var_s1 = (u8 *)M2C_FIELD(gBtlCam, u8 **, 0x600);
    } else {
        var_s1 = (u8 *)gOrbitCam + 0x30;
    }
    temp_f21 = func_0028C610(arg0, 0x40000, 0x32);
    temp_f22 = func_0028C610(arg0, 0x80000, 0x32);
    temp_f23 = func_0028C610(arg0, 0x20000, 0x32);
    if (gBtlCam != NULL) {
        if (*(s32 *)(D_003B0C2C + arg0 * 0x180) & 0x400) {
            temp_f20 = D_00386E38;
            sceVu0InversMatrix(sp + 0x10, var_s1);
            func_00312680(temp_f21 * temp_f20, sp + 0x50, sp + 0x10);
            func_00312638((u8 *)gOrbitCam + 0x10, (u8 *)gOrbitCam + 0x10, sp + 0x50);
            func_00312680(temp_f22 * temp_f20, sp + 0x50, sp + 0x20);
            func_00312638((u8 *)gOrbitCam + 0x10, (u8 *)gOrbitCam + 0x10, sp + 0x50);
        } else {
            M2C_FIELD(gOrbitCam, f32 *, 4) = M2C_FIELD(gOrbitCam, f32 *, 4) + (temp_f21 * D_00386E3C);
            var_f1 = M2C_FIELD(gOrbitCam, f32 *, 4);
            if (var_f1 < D_00386E40) {
                M2C_FIELD(gOrbitCam, f32 *, 4) = var_f1 + D_00386E44;
                var_f1 = M2C_FIELD(gOrbitCam, f32 *, 4);
            }
            if (D_00386E48 < var_f1) {
                M2C_FIELD(gOrbitCam, f32 *, 4) = var_f1 - D_00386E4C;
            }
            M2C_FIELD(gOrbitCam, f32 *, 0) = M2C_FIELD(gOrbitCam, f32 *, 0) - (temp_f22 * D_00386E3C);
            var_f0 = M2C_FIELD(gOrbitCam, f32 *, 0);
            if (var_f0 < D_00386E50) {
                M2C_FIELD(gOrbitCam, f32 *, 0) = D_00386E50;
                var_f0 = M2C_FIELD(gOrbitCam, f32 *, 0);
            }
            if (D_00386E54 < var_f0) {
                M2C_FIELD(gOrbitCam, f32 *, 0) = D_00386E54;
            }
        }
    } else {
        M2C_FIELD(gOrbitCam, f32 *, 4) = M2C_FIELD(gOrbitCam, f32 *, 4) + (temp_f21 * D_00386E58);
        var_f1_2 = M2C_FIELD(gOrbitCam, f32 *, 4);
        if (var_f1_2 < D_00386E5C) {
            M2C_FIELD(gOrbitCam, f32 *, 4) = var_f1_2 + D_00386E60;
            var_f1_2 = M2C_FIELD(gOrbitCam, f32 *, 4);
        }
        if (D_00386E64 < var_f1_2) {
            M2C_FIELD(gOrbitCam, f32 *, 4) = var_f1_2 - D_00386E68;
        }
        M2C_FIELD(gOrbitCam, f32 *, 0) = M2C_FIELD(gOrbitCam, f32 *, 0) - (temp_f22 * D_00386E6C);
        var_f0_2 = M2C_FIELD(gOrbitCam, f32 *, 0);
        if (var_f0_2 < D_00386E70) {
            M2C_FIELD(gOrbitCam, f32 *, 0) = D_00386E70;
            var_f0_2 = M2C_FIELD(gOrbitCam, f32 *, 0);
        }
        if (var_f0_2 > 0.0f) {
            M2C_FIELD(gOrbitCam, f32 *, 0) = 0.0f;
        }
        M2C_FIELD(gOrbitCam, f32 *, 0x10) = 0.0f;
        M2C_FIELD(gOrbitCam, f32 *, 0x18) = 0.0f;
    }
    M2C_FIELD(gOrbitCam, f32 *, 0x20) = M2C_FIELD(gOrbitCam, f32 *, 0x20) + (temp_f23 * 0.5f);
    var_f0_3 = M2C_FIELD(gOrbitCam, f32 *, 0x20);
    temp_f1 = M2C_FIELD(gOrbitCam, f32 *, 0x24);
    if (var_f0_3 < temp_f1) {
        M2C_FIELD(gOrbitCam, f32 *, 0x20) = temp_f1;
        var_f0_3 = M2C_FIELD(gOrbitCam, f32 *, 0x20);
    }
    temp_f1_2 = M2C_FIELD(gOrbitCam, f32 *, 0x28);
    if (temp_f1_2 < var_f0_3) {
        M2C_FIELD(gOrbitCam, f32 *, 0x20) = temp_f1_2;
    }
    /* sp[0] = cos(yaw) * sin(pitch); sp[4] = -sin(yaw); sp[8] = cos(yaw) * cos(pitch) */
    temp_f20 = cosf(M2C_FIELD(gOrbitCam, f32 *, 0));
    temp_f20 = temp_f20 * sinf(M2C_FIELD(gOrbitCam, f32 *, 4));
    *(f32 *)(sp + 0x0) = temp_f20;
    *(f32 *)(sp + 0x4) = -sinf(M2C_FIELD(gOrbitCam, f32 *, 0));
    temp_f20 = cosf(M2C_FIELD(gOrbitCam, f32 *, 0));
    temp_f20 = temp_f20 * cosf(M2C_FIELD(gOrbitCam, f32 *, 4));
    *(f32 *)(sp + 0x8) = temp_f20;
    func_00312680(M2C_FIELD(gOrbitCam, f32 *, 0x20), sp, sp);
    func_00312650(sp, (u8 *)gOrbitCam + 0x10, sp);
    func_0025BDD0(var_s1, sp, gOrbitCam);
    if (gBtlCam != NULL) {
        func_003126C8((u8 *)M2C_FIELD(gBtlCam, u8 **, 0x600) + 0x270, sp);
        return;
    }
    func_003126C8((u8 *)gOrbitCam + 0x280, sp);
}
