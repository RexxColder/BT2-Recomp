#include "common.h"

extern s32 rand(void);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern u8 *func_001BCC38(u8 *emitter);
extern s32 func_001BCB48(u8 *p, s32 arg1);
extern void func_001BCD58(u8 *p);
extern void func_001BCDA0(u8 *emitter, u8 *p);
extern void func_001BCE58(u8 *p);
extern void Vec4_Set(void *dst, f32 x, f32 y, f32 z, f32 w);
extern void Mtx_RotateX(f32 ang, void *dst, void *src);
extern void Mtx_RotateZ(f32 ang, void *dst, void *src);
extern void func_00129C50(void *dst, void *mtx, void *src);
extern void func_00129C28(void *dst, void *src);
extern void func_00129BD0(void *dst, void *src, f32 scale);
extern void func_00129BB8(void *dst, void *src, f32 scale);
extern void Vec3_Add(void *dst, void *a, void *b);
extern void Vec3_Sub(void *dst, void *a, void *b);
extern void Vec3_Normalize(void *dst, void *src);
extern f32 D_00385104, D_00385108, D_0038510C, D_00385110, D_00385114, D_00385118, D_0038511C, D_00385120;

#define F(p, off) (*(f32 *)((p) + (off)))
#define RND(div) ((f32)rand() / (div))

/* Particle spawner: creates `count` particles from emitter (u8 *em) using the parameter blocks of
   the spawn record (sp8+0x38 = d, sp8+0x3C = e). Returns 1, or 0 when no slot is free / init fails. */
s32 func_001BCEE0(u8 *em, u8 *spawn, s32 count) {
    f32 tmp[4];
    f32 trail[4];
    f32 trailDir[4];
    u8 *p, *d, *e;
    s32 usedExt;

    if (count <= 0) {
        return 1;
    }
    do {
        f32 life, ang, v, a, k, t;
        s32 hit;

        usedExt = 0;
        p = func_001BCC38(em);
        if (p == 0) {
            return 0;
        }
        d = *(u8 **)(spawn + 0x38);
        e = *(u8 **)(spawn + 0x3C);
        *(u32 *)p |= 1;
        *(s32 *)(p + 0xE8) = 0;
        *(s32 *)(p + 0xF0) = 0;
        *(s32 *)(p + 0xF4) = 0;
        if (d[8] != 0) {
            usedExt = 1;
            if (func_001BCB48(p, d[8]) == 0) {
                func_001BCD58(p);
                func_001BCDA0(em, p);
                *(s32 *)p = 0;
                return 0;
            }
        }
        life = (F(d, 0x18) + F(d, 0x1C) * RND(D_00385104)) * 30.0f;
        *(s32 *)(p + 8) = 0;
        F(p, 0xC) = life;
        F(p, 0x10) = life * F(d, 0x20);
        F(p, 0x14) = life - F(d, 0x7C);
        p[5] = d[5];
        ang = ((F(d, 0x98) - F(d, 0x9C)) * 0.5f) * RND(D_00385104) + F(d, 0x9C) * 0.5f;
        if (d[2] != 0) {
            F(p, 0x60) = 0;
            F(p, 0x64) = sinf(ang);
            F(p, 0x68) = cosf(ang);
            F(p, 0x6C) = 1.0f;
            Mtx_RotateZ(F(em, 0x108), p + 0xA0, em + 0x80);
        } else {
            Vec4_Set(p + 0x60, 0.0f, 0.0f, 1.0f, 1.0f);
            Mtx_RotateX(ang, p + 0xA0, em + 0x80);
            Mtx_RotateZ(F(em, 0x108), p + 0xA0, p + 0xA0);
        }
        func_00129C50(p + 0x60, p + 0xA0, p + 0x60);
        func_00129C50(p + 0x60, em + 0xC0, p + 0x60);
        func_00129BD0(p + 0x40, p + 0x60, F(d, 0x28) + F(d, 0x2C) * RND(D_00385104));
        F(p, 0x4C) = 1.0f;
        v = F(d, 0x24);
        if (0.0f < v || v < 0.0f) {
            Vec4_Set(tmp, 0.0f, v, 0.0f, 1.0f);
            func_00129C50(tmp, p + 0xA0, tmp);
            func_00129C50(tmp, em + 0xC0, tmp);
            Vec3_Add(p + 0x40, p + 0x40, tmp);
            F(p, 0x4C) = 1.0f;
        }
        Vec3_Sub(p + 0x90, spawn + 0x20, p + 0x60);
        F(p, 0x9C) = 1.0f;
        Vec3_Normalize(p + 0x90, p + 0x90);
        func_00129BD0(p + 0x90, p + 0x90, F(d, 0x80));
        F(p, 0x94) = F(p, 0x94) + F(d, 0x84);
        v = F(d, 0x88);
        F(p, 0x38) = v;
        if (0.0f < v) {
            t = F(d, 0x8C) * RND(D_0038510C);
            F(p, 0x30) = t;
            if (D_00385110 <= t) {
                F(p, 0x30) = t - D_00385108;
            }
            F(p, 0x34) = F(d, 0x90) + (F(d, 0x94) - F(d, 0x90)) * RND(D_0038510C);
        }
        F(p, 0x70) = F(e, 0x20) * RND(D_00385114);
        F(p, 0x74) = F(e, 0x24) * RND(D_00385114);
        F(p, 0x78) = F(e, 0x28) * RND(D_00385114);
        Vec3_Add(p + 0x70, p + 0x70, e + 0x10);
        *(s32 *)(p + 0x7C) = 0;
        *(s32 *)(p + 0x80) = 0;
        *(s32 *)(p + 0x84) = 0;
        *(s32 *)(p + 0x88) = 0;
        F(p, 0x8C) = (F(e, 0x1C) + F(e, 0x2C) * RND(D_00385114)) / F(d, 0x78);
        if (d[4] == 0 || (d[4] == 1 && (rand() & 1) == 0)) {
            F(p, 0x80) = F(e, 0x40) * RND(D_00385114);
            F(p, 0x84) = F(e, 0x44) * RND(D_00385114);
            F(p, 0x88) = F(e, 0x48) * RND(D_00385114);
            Vec3_Add(p + 0x80, p + 0x80, e + 0x30);
            Vec3_Sub(p + 0x80, p + 0x80, e + 0x10);
            func_00129BD0(p + 0x80, p + 0x80, 1.0f / F(p, 0xC));
        }
        F(p, 0x18) = F(d, 0x30) + F(d, 0x34) * RND(D_00385104);
        F(p, 0x20) = F(d, 0x48) + F(d, 0x4C) * RND(D_00385104);
        F(p, 0x28) = F(d, 0x60) + F(d, 0x64) * RND(D_00385104);
        F(p, 0x18) = F(p, 0x18) * F(spawn, 4);
        F(p, 0x20) = F(p, 0x20) * F(spawn, 4);
        F(p, 0x28) = F(p, 0x28) * F(spawn, 4);
        F(p, 0x1C) = (((F(d, 0x38) + F(d, 0x3C) * RND(D_00385104)) * F(spawn, 4)) - F(p, 0x18)) / F(p, 0x10);
        F(p, 0x24) = (((F(d, 0x50) + F(d, 0x54) * RND(D_00385104)) * F(spawn, 4)) - F(p, 0x20)) / F(p, 0x10);
        F(p, 0x2C) = (((F(d, 0x68) + F(d, 0x6C) * RND(D_00385104)) * F(spawn, 4)) - F(p, 0x28)) / F(p, 0x10);
        func_00129BB8(p + 0x80, p + 0x80, 1.0f);
        if (d[1] == 1) {
            f32 sc = F(p, 0x18);
            f32 slope = F(p, 0x1C);
            f32 span = F(p, 0xC) - F(p, 0x10);
            f32 step = 0.0f;
            f32 dir[4];
            s32 sw = 0;

            func_00129C28(trailDir, p + 0x60);
            if (0.0f < F(p, 0xC)) {
                do {
                    func_00129BD0(trail, trailDir, sc);
                    Vec3_Add(p + 0x40, p + 0x40, trail);
                    if (sw != 0) {
                        step = step + 1.0f;
                    } else {
                        hit = (F(p, 0x10) <= step);
                        step = step + 1.0f;
                        if (hit) {
                            sw = 1;
                            slope = ((F(d, 0x40) + F(d, 0x44) * D_00385118) - sc) / span;
                        }
                    }
                    sc = sc + slope;
                } while (step < F(p, 0xC));
            }
            func_00129BD0(p + 0x60, p + 0x60, -1.0f);
        }
        if (usedExt != 0) {
            func_001BCE58(p);
        }
        a = F(em, 0x108) + (F(d, 0x10) + F(d, 0x14) * RND(D_00385104));
        F(em, 0x108) = a;
        k = a;
        if (D_0038511C <= a) {
            k = a - D_00385108;
            F(em, 0x108) = k;
        } else if (a <= D_00385120) {
            k = a + D_00385108;
            F(em, 0x108) = k;
        }
        *(s32 *)(em + 0x68) = *(s32 *)(em + 0x68) + 1;
        count--;
    } while (count > 0);
    return 1;
}
