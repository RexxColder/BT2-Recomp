#include "common.h"

extern s32 func_00115778(s32 arg0, s64 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0, f32 farg1);
extern void func_00208980(s32 arg0, u8 *arg1);
extern void func_00312650(void *arg0, void *arg1, void *arg2);
extern void sceVu0Normalize(void *arg0, void *arg1);
extern f32 sceVu0InnerProduct(void *arg0, void *arg1);
extern void sceVu0ApplyMatrix(u8 *dst, u8 *m, u8 *v);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 atan2f(f32 y, f32 x);
extern f32 D_00383F10;
extern f32 D_00383F14;
extern u8 *D_00387A40;

s32 func_00115B10(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, u32 arg4) {
    u8 buf[0x20];
    f32 dir[4];
    f32 v1[4];
    f32 v2[4];
    f32 pa[4];
    f32 pb[4];
    f32 d[4];
    f32 mtx[8];
    f32 *cam = (f32 *)arg1;
    f32 ip1, ip2, ang, ang2, len, over, f;
    s32 flag;

    flag = (arg4 & 0xFF) == 0;
    func_00208980(arg2, buf);
    f = *(f32 *)(buf + 4);
    dir[0] = sinf(f);
    dir[1] = 0.0f;
    dir[2] = cosf(f);
    dir[3] = 1.0f;

    v1[0] = cam[44];
    v1[2] = cam[52];
    v1[1] = 0.0f;
    sceVu0Normalize(v1, v1);
    ip1 = sceVu0InnerProduct(v1, dir);

    v2[0] = cam[46];
    v2[2] = cam[54];
    v2[1] = 0.0f;
    sceVu0Normalize(v2, v2);
    ip2 = sceVu0InnerProduct(v2, dir);

    ang = atan2f(ip1, ip2);
    ang2 = (1.0f - cam[5] * D_00383F10) + 0.25f;

    if (arg3 == -1) {
        return func_00115778(arg0, 0x3F800000801D94F7LL, 0x800, 0x800, 0, ang, ang2);
    }

    pa[0] = (f32)(s32)(*(f32 *)(*(u8 **)D_00387A40 + arg2 * 0x18580 + 0x9C0) * 100.0f) * D_00383F14;
    pa[1] = 0.0f;
    pa[2] = (f32)(s32)(*(f32 *)(*(u8 **)D_00387A40 + arg2 * 0x18580 + 0x9C8) * 100.0f) * D_00383F14;
    pa[3] = 1.0f;
    pb[0] = (f32)(s32)(*(f32 *)(*(u8 **)D_00387A40 + arg3 * 0x18580 + 0x9C0) * 100.0f) * D_00383F14;
    pb[1] = 0.0f;
    pb[2] = (f32)(s32)(*(f32 *)(*(u8 **)D_00387A40 + arg3 * 0x18580 + 0x9C8) * 100.0f) * D_00383F14;
    pb[3] = 1.0f;
    func_00312650(d, pb, pa);
    len = __builtin_sqrtf(__builtin_fabsf(sceVu0InnerProduct(d, d)));
    over = cam[0] - 170.0f;
    if (over < len) {
        flag = 1;
        pa[0] = pb[0] - (d[0] * over) / len;
        pa[2] = pb[2] - (d[2] * over) / len;
    }
    sceVu0ApplyMatrix((u8 *)mtx, arg1 + 0x70, (u8 *)pa);
    return func_00115778(arg0, 0x3F80000080FE0092LL, (s32)mtx[0], (s32)mtx[1], flag, ang, ang2);
}
