#include "common.h"

/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(out, x) do { \
    (out) = (s32)(x); \
} while (0)

f32 EftMath_WrapAngle(f32 farg0);
s32 func_001F3758(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
void Mtx_StoreIdentity(s32 arg0);
void Vec3_Normalize(s32 arg0, s32 arg1);
void Vec3_RotateAxis(f32 farg0, s32 arg1, s32 arg2, s32 arg3);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void func_00129C28();
void func_00129C50(s32 arg0, s32 arg1, s32 arg2);
f32 func_00129E08(s32 arg0);
s32 func_00195818(s32 arg0);
void func_00208798(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_00208F98(s32 arg0, s32 arg1, s32 arg2);
s32 func_0020B3D0(s32 arg0);
extern f32 D_00384698;
extern f32 D_0038469C;
extern f32 D_003846A0;
extern f32 D_003846A4;

void func_001561C8(s32 arg0) {
    u8 fr[0x160];
    s32 v;
    s32 s0;
    s32 s2;
    s32 s3;
    s32 k;
    f32 f0;
    f32 f20;

    v = func_001F3758(arg0);
    s3 = *(s32 *)(arg0 + 0x38);
    s2 = *(s32 *)(s3 + 0xA0);
    s0 = *(s32 *)(v + 0x38);

    memset(&fr[0x50], 0, 0x10);
    *(f32 *)&fr[0x5C] = 1.0f;
    memset(&fr[0x60], 0, 0x10);
    *(f32 *)&fr[0x6C] = 1.0f;
    *(s32 *)&fr[0x70] = s2;
    *(s32 *)&fr[0x74] = s0;
    *(s32 *)&fr[0x78] = *(s32 *)(s0 + 0x1E80);
    *(s32 *)&fr[0x7C] = *(s32 *)(s2 + 0);
    CVT_W_S(*(s32 *)&fr[0x80], *(f32 *)(s2 + 0x10) * 30.0f);
    *(s32 *)&fr[0x84] = *(s32 *)(s3 + 0xAA0);
    *(s32 *)&fr[0x88] = *(s32 *)(s3 + 0xAA0) * 2 + 1;
    *(f32 *)&fr[0x8C] = 10.0f;
    *(f32 *)&fr[0x90] = *(f32 *)(*(s32 *)(s2 + 0x24) + 0x10);
    *(f32 *)&fr[0x94] = D_00384698;
    *(f32 *)&fr[0x98] = 6.0f;

    /* the 0x50 bytes at fr+0x50 are copied to fr+0x00 in dwords (ld/sd) */
    for (k = 0; k < 10; k++) {
        *(s64 *)&fr[k * 8] = *(s64 *)&fr[0x50 + k * 8];
    }

    func_00129C28((s32)&fr[0x00], s3 + 0x40, (s32)&fr[0x90], (s32)&fr[0x40]);
    func_00129C28((s32)&fr[0x10], s3 + 0x20);
    if (*(s32 *)(*(s32 *)(s2 + 0x20)) == 0x6A) {
        v = func_0020B3D0(*(s32 *)(s2 + 0));
        func_00208DE8(v, (s32)&fr[0x50], 3);
        func_00208798(*(s32 *)(s2 + 0), (s32)&fr[0x60]);
        Vec3_Sub((s32)&fr[0x70], (s32)&fr[0x50], (s32)&fr[0x60]);
        Vec3_Normalize((s32)&fr[0x10], (s32)&fr[0x70]);
        *(s32 *)&fr[0x74] = 0;
        f0 = func_00129E08((s32)&fr[0x70]);
        f20 = f0 * D_0038469C;
        if (1.5f < f20) {
            f20 = 1.5f;
        }
        Mtx_StoreIdentity((s32)&fr[0xA0]);
        Mtx_StoreIdentity((s32)&fr[0xE0]);
        func_00208F98(*(s32 *)(s2 + 0), (s32)&fr[0xE0], 0x30);
        f0 = EftMath_WrapAngle(f20 * D_003846A0);
        Vec3_RotateAxis(f0, (s32)&fr[0x10], (s32)&fr[0x10], (s32)&fr[0xE0]);
        func_00129C50((s32)&fr[0x10], (s32)&fr[0xA0], (s32)&fr[0x10]);
        *(f32 *)&fr[0x40] = D_003846A4;
    }

    v = func_00195818((s32)&fr[0x00]);
    k = *(s32 *)(s3 + 0xAA0);
    *(s32 *)(s3 + k * 4 + 0xAA4) = v;
    *(s32 *)(s3 + 0xAA0) = *(s32 *)(s3 + 0xAA0) + 1;
}
