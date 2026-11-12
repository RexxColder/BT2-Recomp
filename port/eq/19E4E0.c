#include "common.h"

extern f32 D_00384DB4, D_00384DB8, D_00384DBC, D_00384DC0, D_00384DC4, D_00384DC8;
extern f32 D_00384DCC, D_00384DD0, D_00384DD4;
extern u8 D_0036D930[];
extern u8 D_00387800[];
extern u8 *D_003877F8;

s32 Rand_IntRange(s32 lo, s32 hi);
f32 Rand_FloatRange(f32 lo, f32 hi);
f32 sinf(f32 x);
f32 cosf(f32 x);
void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
void func_00129B58(u8 *dst, u8 *a, u8 *b);
void func_00129BD0(u8 *dst, u8 *src, f32 s);
void func_00129C28(u8 *dst, u8 *src);
u8 *func_001C1FC0(void);
void func_001C2260(u8 *p);
void func_0019D850(u8 *p, s32 a1, s32 a2, s32 a3);
void func_001C1560(u8 *p, u8 *q, s32 lo, s32 hi, f32 f);
void func_001C16A0(u8 *p, u8 *q, s32 lo, s32 hi, u8 *v0, u8 *v1);
void func_001C1650(u8 *p, u8 *q, s32 lo, s32 hi, f32 a, f32 b);
void func_001C1790(u8 *p, u8 *q, s32 a2, s32 a3, s32 t0, u8 *t1, s32 t2);
void func_001C15F8(u8 *p, u8 *q, s32 a2, s32 a3, s32 t0, s32 t1);

void func_0019E4E0(u8 *cfg, u8 *cfg2, s32 extra, u8 *center, u8 *vel) {
    u8 sp[0x50] __attribute__((aligned(16)));
    f32 step;
    f32 f;
    s32 ring;
    s32 j;
    u8 *cntp;
    u8 *p;
    u8 *q;
    s32 r;
    s32 lo;
    s32 hi;
    s32 tmp;

    step = 360.0f / (f32)cfg[0xB];
    ring = 1;
    if (!(ring < (cfg[0xB] >> 1))) {
        return;
    }
    cntp = cfg + 0xC;
    do {
        if (*cntp != 0) {
            j = 0;
            do {
                f32 rad, angle, angle2, rs1, rc1, sinA, cosA, sinB, cosB, rj, per, x0, z0;

                r = Rand_IntRange(0, cfg[0xA]);
                rad = (f32)(cfg[9] + r);
                angle = (f32)ring * step + Rand_FloatRange(step * D_00384DB8, step * D_00384DBC);
                rad = rad * D_00384DB4;
                angle = angle / 180.0f * D_00384DC0;
                sinA = sinf(angle);
                cosA = cosf(angle);
                per = 360.0f / (f32)*cntp;
                rs1 = rad * sinA;
                rc1 = rad * cosA;
                rj = Rand_FloatRange(per * D_00384DB8, per * D_00384DBC);
                angle2 = ((f32)j + (f32)(ring - ((ring + ((u32)ring >> 31)) >> 1) * 2) * 0.5f) * per + rj;
                angle2 = angle2 / 180.0f * D_00384DC0;
                cosB = cosf(angle2);
                sinB = sinf(angle2);
                z0 = rs1 * sinB;
                x0 = rs1 * cosB;
                Vec4_Set(sp, x0 + *(f32 *)(center + 0), rc1 + *(f32 *)(center + 4), z0 + *(f32 *)(center + 8),
                         1.0f);
                p = func_001C1FC0();
                if (p != NULL) {
                    func_001C2260(p);
                    q = p + 0x20;
                    *(s16 *)(p + 4) = (s16)(cfg[3] + Rand_IntRange(0, cfg[4]));
                    tmp = cfg[5] + Rand_IntRange(0, cfg[6]);
                    *(s16 *)(p + 6) = (s16)~tmp;
                    func_00129C28(q, sp);
                    p[2] = cfg[0] & 1;
                    if (*(u16 *)cfg & 2) {
                        if (Rand_IntRange(0, 1) == 1) {
                            p[1] |= 0x10;
                        }
                    }
                    if (*(u16 *)cfg & 4) {
                        if (Rand_IntRange(0, 1) == 1) {
                            p[1] |= 0x20;
                        }
                    }
                    if (*(u16 *)cfg & 8) {
                        p[1] |= 1;
                    }
                    {
                        u8 shade = (u8)Rand_IntRange(0, cfg2[8]);
                        p[0x18] = (u8)(shade + (cfg2[0] + Rand_IntRange(0, cfg2[4])));
                        p[0x19] = (u8)(shade + (cfg2[1] + Rand_IntRange(0, cfg2[5])));
                        p[0x1A] = (u8)(shade + (cfg2[2] + Rand_IntRange(0, cfg2[6])));
                    }
                    p[0x1B] = (u8)(cfg2[3] + Rand_IntRange(0, cfg2[7]));
                    *(f32 *)(p + 0x1C) = 1.0f;
                    func_0019D850(p, *(s32 *)D_003877F8, cfg[2] + extra, (*(u16 *)cfg >> 8) & 1);
                    if (*(u16 *)cfg & 0x10) {
                        *(f32 *)(p + 0x14) = Rand_FloatRange(D_00384DC4, D_00384DC8);
                    }
                    r = Rand_IntRange(0, cfg[8]);
                    *(f32 *)(p + 0x10) = (f32)(cfg[7] + r) * 5.0f;
                    if (cfg[0x13] < cfg[0x14]) {
                        hi = cfg[0x14];
                        lo = cfg[0x13];
                        r = Rand_IntRange(0, (s8)cfg[0x16]);
                        f = (f32)((s8)cfg[0x15] + r) * D_00384DBC;
                        func_001C1560(p, p + 0x10, lo, hi, f);
                    }
                    if (cfg[0x17] < cfg[0x18]) {
                        if (vel != NULL) {
                            hi = cfg[0x17];
                            lo = cfg[0x18];
                            func_00129BD0(sp + 0x10, vel, (f32)(s8)cfg[0x19] * D_00384DB4);
                            func_00129BD0(sp + 0x20, vel, (f32)(s8)cfg[0x1A] * D_00384DB4);
                            func_001C16A0(p, q, hi, lo, sp + 0x10, sp + 0x20);
                        }
                    }
                    if (cfg[0x1B] < cfg[0x1C]) {
                        hi = cfg[0x1C];
                        lo = cfg[0x1B];
                        func_00129B58(sp + 0x30, sp, center);
                        r = Rand_IntRange(0, cfg[0x1E]);
                        func_00129BD0(sp + 0x30, sp + 0x30, (f32)(cfg[0x1D] + r) * D_00384DCC);
                        func_001C16A0(p, q, lo, hi, sp + 0x30, D_0036D930);
                    }
                    if (cfg[0x1F] < cfg[0x20]) {
                        hi = cfg[0x20];
                        lo = cfg[0x1F];
                        func_00129B58(sp + 0x40, sp, center);
                        r = Rand_IntRange(0, cfg[0x22]);
                        func_00129BD0(sp + 0x40, sp + 0x40, (f32)(cfg[0x21] + r) * D_00384DD0);
                        *(f32 *)(sp + 0x44) = 0.0f;
                        func_001C16A0(p, q, lo, hi, sp + 0x40, D_0036D930);
                    }
                    if (cfg[0x23] < cfg[0x24]) {
                        f32 a, b;
                        hi = cfg[0x24];
                        lo = cfg[0x23];
                        r = Rand_IntRange(0, (s8)cfg[0x26]);
                        a = (f32)((s8)cfg[0x25] + r);
                        r = Rand_IntRange(0, -2);
                        tmp = ((cfg[0xB] >> 1) - ring - 1) * cfg[0x27];
                        b = (f32)(r - tmp);
                        func_001C1650(p, p + 0x24, lo, hi, a * D_00384DB4, b * D_00384DB4);
                    }
                    if (*(u16 *)cfg & 0x100) {
                        s32 s0 = *(s16 *)(p + 4);
                        s32 d;
                        d = s0 / 16;
                        func_001C1790(p, p + 0xC, 1, s0, d != 0 ? d : 1, D_00387800, 4);
                        d = *(s16 *)(p + 4) / 4;
                        func_001C1790(p, p + 0xD, 1, s0, d != 0 ? d : 1, D_00387800, 4);
                    }
                    {
                        s32 s0;
                        s32 sgn;
                        s0 = *(s16 *)(p + 4);
                        sgn = Rand_IntRange(0, 1) * 2 - 1;
                        func_001C1650(p, p + 0x14, 0, s0, (f32)cfg[0x28] * D_00384DD4 * (f32)sgn, 0.0f);
                    }
                    if (cfg[0x29] != 0) {
                        func_001C15F8(p, p + 0x1B, 0, cfg[0x29], 0, p[0x1B]);
                    }
                    if (cfg[0x2A] != 0) {
                        s32 u = *(u16 *)(p + 4);
                        func_001C15F8(p, p + 0x1B, (s16)(u - cfg[0x2A]), (s16)u, p[0x1B], 0);
                    }
                }
                j = j + 1;
            } while (j < *cntp);
        }
        ring = ring + 1;
        cntp = cntp + 1;
    } while (ring < (cfg[0xB] >> 1));
}
