#include "common.h"

extern void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
extern void func_00312650(void *arg0, void *arg1, void *arg2);
extern void sceVu0Normalize(void *arg0, void *arg1);
extern f32 sceVu0InnerProduct(void *arg0, void *arg1);
extern void EftBolt_AllocSegs(u8 *arg0, s32 arg1);
extern void EftBolt_FreeSegs(u8 *arg0);
extern void func_0017D658(u8 *arg0, void *arg1, void *arg2, f32 farg0);
extern f32 D_00384AC4;

/* Initialises a bolt record between two endpoints: stores owner/id fields, builds the four
   corner points (base + dir * length +- half-width vectors), the centre direction and an
   inward-shrunk width, allocates 3..10 segments by length and queues it. Returns 1 on success. */
s32 func_0017E8A0(u8 *ctx, u8 *rec, s32 owner, s32 a3, s32 t0, s32 t1, f32 *va, f32 *vb, f32 scale, f32 length) {
    u8 sp[0x40];
    f32 *p0 = (f32 *)(sp + 0x00);
    f32 *p1 = (f32 *)(sp + 0x10);
    f32 *dir = (f32 *)(sp + 0x20);
    f32 *diff = (f32 *)(sp + 0x30);
    f32 *base = (f32 *)(rec + 0x30);
    f32 k;
    f32 ip;
    f32 mx, my, mz;
    s32 n;

    *(s32 *)(rec + 0x10) = a3;
    *(s32 *)(rec + 0xC) = *(s32 *)(rec + 0xC) | 1;
    *(s32 *)(rec + 0x18) = t1;
    *(s32 *)(rec + 0x14) = t0;
    *(f32 *)(rec + 0x1C) = 30.0f;
    func_00208DE8(owner, base, t0);
    *(f32 *)(rec + 0x50) = va[0] * scale;
    *(f32 *)(rec + 0x58) = 1.0f;
    *(f32 *)(rec + 0x54) = va[1] * scale;
    *(f32 *)(rec + 0x60) = vb[0] * scale;
    *(f32 *)(rec + 0x20) = length;
    *(f32 *)(rec + 0x68) = 1.0f;
    *(f32 *)(rec + 0x64) = vb[1] * scale;
    func_00208DE8(owner, dir, *(s32 *)(rec + 0x18));
    func_00312650(dir, dir, base);

    mx = dir[0] * *(f32 *)(rec + 0x20);
    my = dir[1] * *(f32 *)(rec + 0x20);
    mz = dir[2] * *(f32 *)(rec + 0x20);
    p0[3] = 1.0f;
    p1[3] = 1.0f;
    p0[0] = base[0] + mx + *(f32 *)(rec + 0x50);
    p1[0] = base[0] + mx + *(f32 *)(rec + 0x60);
    p1[1] = base[1] + my + *(f32 *)(rec + 0x64);
    p1[2] = base[2] + mz + *(f32 *)(rec + 0x68);
    p0[1] = base[1] + my + *(f32 *)(rec + 0x54);
    p0[2] = base[2] + mz + *(f32 *)(rec + 0x58);
    func_00312650(diff, p1, p0);
    sceVu0Normalize(rec + 0x70, diff);

    *(f32 *)(rec + 0x80) = (va[0] + vb[0]) * 0.5f;
    *(f32 *)(rec + 0x84) = (va[1] + vb[1]) * 0.5f;
    *(f32 *)(rec + 0x8C) = 1.0f;
    *(f32 *)(rec + 0x88) = (va[2] + vb[2]) * 0.5f;
    sceVu0Normalize(rec + 0x80, rec + 0x80);

    k = *(f32 *)(ctx + 0xEA0) * D_00384AC4;
    *(f32 *)(rec + 0x54) = *(f32 *)(rec + 0x54) - *(f32 *)(rec + 0x84) * k;
    *(f32 *)(rec + 0x64) = *(f32 *)(rec + 0x64) - *(f32 *)(rec + 0x84) * k;
    *(f32 *)(rec + 0x58) = *(f32 *)(rec + 0x58) - *(f32 *)(rec + 0x88) * k;
    *(f32 *)(rec + 0x68) = *(f32 *)(rec + 0x68) - *(f32 *)(rec + 0x88) * k;
    *(f32 *)(rec + 0x50) = *(f32 *)(rec + 0x50) - *(f32 *)(rec + 0x80) * k;
    *(f32 *)(rec + 0x60) = *(f32 *)(rec + 0x60) - *(f32 *)(rec + 0x80) * k;

    ip = sceVu0InnerProduct(diff, diff);
    n = (s32)(__builtin_sqrtf(__builtin_fabsf(ip)) / *(f32 *)(ctx + 0xEA0) + 3.0f);
    if (n >= 11) {
        n = 10;
    }
    EftBolt_AllocSegs(rec, n);
    if (*(s32 *)(rec + 8) < 3) {
        EftBolt_FreeSegs(rec);
        return 0;
    }
    func_0017D658(rec, p0, p1, *(f32 *)(ctx + 0xEA0));
    *(s32 *)(ctx + 0xE78) = *(s32 *)(ctx + 0xE78) + 1;
    return 1;
}
