#include "common.h"
#include "m2c_macros.h"

extern f32 D_00385098;
extern f32 D_0038509C;
extern f32 D_003850A0;
extern f32 D_003850A4;
extern f32 D_003850A8;
extern f32 D_003850AC;
extern f32 D_003850B0;
extern f32 D_003850B4;
extern f32 D_003850B8;
extern f32 D_003850BC;
extern f32 D_003850C0;
extern f32 D_003850C4;
extern f32 D_003850C8;
extern f32 D_003850CC;
extern f32 D_003850D0;
extern f32 D_003850D4;
extern f32 D_003850D8;
extern f32 D_003850DC;
extern f32 D_003850E0;
extern f32 D_003850E4;
extern f32 D_003850E8;

void EftPtcl3_PickTexture(void *a0, s32 a1, s32 a2, s32 a3);
f32 Mathf_Asin(f32 farg0);
void Mtx_RotateX(f32 farg0, void *a1, void *a2);
void Mtx_RotateY(f32 farg0, void *a1, void *a2);
void Mtx_StoreIdentity(void *a0);
f32 atan2f(f32 farg0, f32 farg1);
void func_00129C28(void *a0, void *a1);
void func_001B8C40(void *a0, void *a1);
s32 rand(void);

void func_001BA160(void *arg0, void *arg1) {
    s32 v1;
    s32 prod;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    void *s3;
    void *s0;
    void *s1;

    v1 = M2C_FIELD(arg0, s32 *, 0x60);
    s3 = M2C_FIELD(arg1, void **, 0x38);
    M2C_FIELD(arg0, s32 *, 0x60) = v1 | 1;
    f1 = M2C_FIELD(arg1, f32 *, 0x0);
    if (f1 <= 0.0f) {
        M2C_FIELD(arg0, s32 *, 0x60) = v1 | 9;
    } else {
        M2C_FIELD(arg0, f32 *, 0x134) = f1 * 30.0f;
    }
    func_001B8C40(arg0, arg1);
    s1 = (u8 *)arg0 + 0x1D0;
    func_00129C28((u8 *)arg0 + 0x150, (u8 *)arg1 + 0x10);
    Mtx_StoreIdentity(s1);
    s0 = (u8 *)arg0 + 0x210;
    M2C_FIELD(arg0, f32 *, 0x250) = Mathf_Asin(-M2C_FIELD(arg1, f32 *, 0x24));
    M2C_FIELD(arg0, f32 *, 0x254) = atan2f(M2C_FIELD(arg1, f32 *, 0x20), M2C_FIELD(arg1, f32 *, 0x28));
    Mtx_RotateX(M2C_FIELD(arg0, f32 *, 0x250), s0, s1);
    Mtx_RotateY(M2C_FIELD(arg0, f32 *, 0x254), s0, s0);

    /* 0x258: rand/D_00385098, clamped into [0,...) by the A0/A4/A8 pair */
    f3 = M2C_FIELD(s3, f32 *, 0x60) + (M2C_FIELD(s3, f32 *, 0x64) * ((f32)rand() / D_00385098));
    M2C_FIELD(arg0, f32 *, 0x258) = f3;
    if (D_0038509C <= f3) {
        M2C_FIELD(arg0, f32 *, 0x258) = f3 - D_003850A0;
    } else if (f3 <= D_003850A4) {
        M2C_FIELD(arg0, f32 *, 0x258) = f3 + D_003850A8;
    }

    /* 0x1B0 */
    f2 = M2C_FIELD(s3, f32 *, 0xF4) + (M2C_FIELD(s3, f32 *, 0xF8) * ((f32)rand() / D_003850AC));
    M2C_FIELD(arg0, f32 *, 0x1B0) = f2;
    if (D_003850B0 <= f2) {
        M2C_FIELD(arg0, f32 *, 0x1B0) = f2 - D_003850B4;
    } else if (f2 <= D_003850B8) {
        M2C_FIELD(arg0, f32 *, 0x1B0) = f2 + D_003850BC;
    }

    /* 0x1C0 and 0x1B4 (both divide by D_003850C0) */
    f0 = D_003850C0;
    M2C_FIELD(arg0, f32 *, 0x1C0) = M2C_FIELD(s3, f32 *, 0xFC) + (M2C_FIELD(s3, f32 *, 0x100) * ((f32)rand() / f0));
    f2 = M2C_FIELD(s3, f32 *, 0x104) + (M2C_FIELD(s3, f32 *, 0x108) * ((f32)rand() / f0));
    M2C_FIELD(arg0, f32 *, 0x1B4) = f2;
    if (D_003850C4 <= f2) {
        M2C_FIELD(arg0, f32 *, 0x1B4) = f2 - D_003850C8;
    } else if (f2 <= D_003850CC) {
        M2C_FIELD(arg0, f32 *, 0x1B4) = f2 + D_003850D0;
    }

    /* 0x1C4 and 0x1B8 (both divide by D_003850D4) */
    f0 = D_003850D4;
    M2C_FIELD(arg0, f32 *, 0x1C4) = M2C_FIELD(s3, f32 *, 0x10C) + (M2C_FIELD(s3, f32 *, 0x110) * ((f32)rand() / f0));
    f2 = M2C_FIELD(s3, f32 *, 0x114) + (M2C_FIELD(s3, f32 *, 0x118) * ((f32)rand() / f0));
    M2C_FIELD(arg0, f32 *, 0x1B8) = f2;
    if (D_003850D8 <= f2) {
        M2C_FIELD(arg0, f32 *, 0x1B8) = f2 - D_003850DC;
    } else if (f2 <= D_003850E0) {
        M2C_FIELD(arg0, f32 *, 0x1B8) = f2 + D_003850E4;
    }

    /* 0x1C8 */
    M2C_FIELD(arg0, f32 *, 0x1C8) = M2C_FIELD(s3, f32 *, 0x11C) + (M2C_FIELD(s3, f32 *, 0x120) * ((f32)rand() / D_003850E8));

    prod = (s32)M2C_FIELD(s3, s16 *, 0x15C) * (s32)M2C_FIELD(s3, s16 *, 0x15E);
    M2C_FIELD(arg0, s32 *, 0x6C) = prod;
    if (prod >= 2) {
        M2C_FIELD(arg0, s32 *, 0x60) = M2C_FIELD(arg0, s32 *, 0x60) | 0x40;
        M2C_FIELD(arg0, f32 *, 0x70) = 1.0f / (f32)M2C_FIELD(s3, s16 *, 0x15C);
        M2C_FIELD(arg0, f32 *, 0x74) = 1.0f / (f32)M2C_FIELD(s3, s16 *, 0x15E);
    } else {
        M2C_FIELD(arg0, f32 *, 0x74) = 1.0f;
        M2C_FIELD(arg0, f32 *, 0x70) = 1.0f;
    }
    EftPtcl3_PickTexture(arg0, M2C_FIELD(arg1, s32 *, 0x34), M2C_FIELD(arg1, s32 *, 0x30), M2C_FIELD(arg1, s32 *, 0x30));
}
