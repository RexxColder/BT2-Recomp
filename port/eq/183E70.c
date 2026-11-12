#include "common.h"

void func_0012D3A0(u8 *a0, u8 *a1, s32 a2);
void func_00208F18(s32 a0, void *a1, s32 a2);
s32 rand(void);
s32 func_0020B3D0(s32 a0);
void func_00208DE8(s32 a0, u8 *a1, s32 a2);
f32 func_00129E50(u8 *a0, void *a1);
void Vec3_Normalize(void *dst, void *src);
extern f32 D_00384B8C;
extern f32 D_00384B90;
extern f32 D_00384B94;

void func_00183E70(u8 *arg0) {
    f32 sp[24];
    u8 *s3;
    u8 *s1;
    f32 f0;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 nf;
    s32 v;

    s3 = arg0 + 0xA90;
    s1 = arg0 + 0xA70;
    f21 = D_00384B8C;
    f20 = D_00384B90;
    func_0012D3A0(s3, s1, *(s32 *)(arg0 + 0xA40));
    func_00208F18(*(s32 *)(arg0 + 0xA40), sp, 0x30);
    f0 = (f32)rand() / f21;
    f22 = f0 * f20;
    f0 = (f32)rand() / f21;
    f0 = f0 * D_00384B94;
    f20 = f0 - f20;
    v = func_0020B3D0(*(s32 *)(arg0 + 0xA40));
    func_00208DE8(v, (u8 *)&sp[16], 0x11);
    f0 = func_00129E50(s1, &sp[16]) / 400.0f;
    if (1.0f < f0) {
        f0 = 1.0f;
    }
    f22 = f22 * f0;
    f20 = f20 * f0;
    nf = -f22;
    *(f32 *)s3 = *(f32 *)s3 + (sp[4] * nf + sp[0] * f20);
    *(f32 *)(arg0 + 0xA94) = *(f32 *)(arg0 + 0xA94) + (sp[5] * nf + sp[1] * f20);
    *(f32 *)(arg0 + 0xA98) = *(f32 *)(arg0 + 0xA98) + (sp[6] * nf + sp[2] * f20);
    Vec3_Normalize(s3, s3);
}
