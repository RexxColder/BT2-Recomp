#include "common.h"

extern f32 D_00384DD8;
extern f32 D_00384DDC;
extern f32 D_00384DE0;
extern f32 D_00384DE4;
extern f32 D_00384DE8;
extern f32 D_00384DEC;
extern f32 D_00384DF0;
extern f32 D_00384DF4;
extern f32 D_00384DF8;
extern f32 D_00384DFC;
extern u8 D_0036D930[];

extern s32 Rand_IntRange(s32 lo, s32 hi);
extern f32 Rand_FloatRange(f32 lo, f32 hi);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
extern void func_00129B58(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Normalize(u8 *dst, u8 *src);
extern void func_00129BD0(u8 *dst, u8 *src, f32 s);
extern void Vec3_Add(u8 *dst, u8 *a, u8 *b);
extern u8 *func_001C1FC0(void);
extern void func_001C2228(u8 *p);
extern void func_0019D880(u8 *p, u8 *cfg, u8 *a, u8 *pos, u8 *b);
extern void func_001C16A0(u8 *p, u8 *vec, s32 lo, s32 hi, u8 *dir, u8 *tbl);
extern void func_001C1720(u8 *p, u8 *vec, s32 lo, s32 hi, f32 a, f32 b, f32 c, f32 d);
extern void func_0019DA58(u8 *p, u8 *cfg, u8 *center, s32 z, u8 *dir, u8 *b, f32 scale, f32 zero);

/* Spawns the sparks of a burst: for each ring i in 1..(count/2-1) of cfg (counts at cfg+0x58+i), `cnt` sparks on
   a sphere of radius r around `center`, each a particle with up to 3 length-segments (cfg+0x62..0x6A) and an
   optional tail (cfg+0x5F..0x61). Always returns 0. */
s32 func_0019ECF0(f32 scale, u8 *cfg, u8 *p1, u8 *center, u8 *p3, u8 *p4) {
    u8 pos[0x10];
    u8 dir[0x10];
    u8 tmp[0x10];
    u8 dir2[0x10];
    u8 *cntp;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    f32 step;
    f32 base;
    f32 sc;
    f32 radius, angA, angB;
    f32 sinA, cosA, sinB, cosB, rr, len, t, tk;
    f32 sz, szLo, szHi;
    u8 *sp;
    u8 *vp;
    s32 lo, hi;

    n = cfg[0x57];
    sc = (f32)cfg[1] * D_00384DD8;
    step = 360.0f / (f32)n;
    sc = scale * sc;
    cntp = cfg + 0x58;
    for (i = 1; i < (n >> 1); i++, cntp++) {
        if (*cntp == 0) {
            continue;
        }
        j = 0;
        do {
            s32 r = Rand_IntRange(0, cfg[0x56]);
            f32 a = Rand_FloatRange(step * D_00384DE8, step * D_00384DEC);
            f32 per;
            f32 b;

            radius = (f32)(cfg[0x55] + r) * D_00384DDC;
            angA = (((f32)i * step + a) / 180.0f) * D_00384DE0;
            sinA = sinf(angA);
            cosA = cosf(angA);
            per = 360.0f / (f32)*cntp;
            b = Rand_FloatRange(per * D_00384DF0, per * D_00384DF4);
            angB = ((((f32)j + (f32)(i % 2) * 0.5f) * per + b) / 180.0f) * D_00384DE0;
            cosB = cosf(angB);
            sinB = sinf(angB);
            Vec4_Set(pos, radius * sinA * cosB + *(f32 *)(center + 0), radius * cosA + *(f32 *)(center + 4),
                     radius * sinA * sinB + *(f32 *)(center + 8), 1.0f);

            sp = func_001C1FC0();
            if (sp != 0) {
                func_001C2228(sp);
                func_0019D880(sp, cfg, p1, pos, p4);
                *(s32 *)(sp + 0xD8) = 0x20;
                *(s32 *)(sp + 0xD4) = 0x20;
                rr = Rand_FloatRange(0.0f, 1.0f);
                len = ((f32)cfg[0x63] + (f32)cfg[0x64] * rr) * sc;
                func_00129B58(dir, pos, center);
                Vec3_Normalize(dir, dir);
                vp = sp + 0x20;
                if (len != 0.0f) {
                    func_00129BD0(tmp, dir, len);
                    Vec3_Add(vp, vp, tmp);
                }
                for (k = 0; k < 3; k++) {
                    s32 h = *(s16 *)(sp + 4);
                    f32 fh1, fh0;
                    t = ((f32)cfg[0x66 + 3 * k] + (f32)cfg[0x67 + 3 * k] * rr) * sc;
                    if (len == t) {
                        continue;
                    }
                    fh1 = (f32)(h * cfg[0x65 + 3 * k]) * D_00384DF8;
                    fh0 = (f32)(h * cfg[0x62 + 3 * k]) * D_00384DF8;
                    hi = (s16)(s32)fh0;
                    lo = (s16)(s32)fh1;
                    if (fh1 != (f32)lo) {
                        lo = (s16)(s32)(fh1 + 1.0f);
                    }
                    if (hi == lo) {
                        continue;
                    }
                    func_00129BD0(dir2, dir, t - len);
                    len = t;
                    func_001C16A0(sp, vp, hi, lo, dir2, D_0036D930);
                }
                if (cfg[0x5F] != 0) {
                    f32 rnd = Rand_FloatRange(0.0f, D_00384DE4);
                    s32 hh = *(s16 *)(sp + 4);
                    s32 h0 = (s16)(hh - cfg[0x5F]);
                    szLo = (f32)cfg[0x60] * sc * D_00384DDC;
                    szHi = (f32)cfg[0x61] * sc * D_00384DDC;
                    func_001C1720(sp, vp, h0, hh, szLo, szHi, rnd, rnd + D_00384DE4);
                    rnd += D_00384DFC;
                    func_001C1720(sp, sp + 0x28, h0, hh, szLo, szHi, rnd, rnd + D_00384DE4);
                }
                func_00129B58(dir2, vp, center);
                Vec3_Normalize(dir2, dir2);
                func_0019DA58(sp, cfg, center, 0, dir2, p3, sc, 0.0f);
            }
        } while (++j < *cntp);
    }
    return 0;
}
