#include "common.h"

extern f32 D_00384F60;
extern f32 D_00384F64;
extern f32 D_00384F68;
extern f32 D_00384F6C;
extern f32 D_00384F70;

s32 rand(void);
void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Vec3_Normalize(void *arg0, void *arg1);
void Vec3_Sub(void *arg0, void *arg1, void *arg2);
f32 func_00129CD8(u8 *arg0, u8 *arg1);
void func_00129C50(void *arg0, void *arg1, void *arg2);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void func_00129C28(void *arg0, void *arg1);
void func_00129C38(void *arg0, void *arg1);
void Mtx_RotateX(void *dst, void *src, f32 ang);
void Mtx_RotateY(void *dst, void *src, f32 ang);
void Mtx_StoreIdentity(void *arg0);

/* Spawns/initialises a linked list of particles (next ptr at +0x60) for a burst emitter.
   task data d = task[0x38], cfg = d[0x38]; e = emitter (e[0] = first particle). */
void func_001B0DF8(u8 *task, u8 *e) {
    u8 sp[0xc0];   /* tamano de locales del original (antes 0xb0) */
    u8 *mat = sp;
    u8 *ident = sp + 0x40;
    u8 *dir = sp + 0x80;
    u8 *vecT = sp + 0x90;
    u8 *prev = sp + 0xA0;
    u8 *d = *(u8 **)(task + 0x38);
    u8 *cfg = *(u8 **)(d + 0x38);
    u8 *p;
    f32 F = D_00384F60;
    f32 pos;
    f32 step;
    f32 a;
    f32 b;
    f32 len;
    f32 ang;
    s32 idx = 0;
    s32 ra;
    s32 rb;

    pos = *(f32 *)(cfg + 0x3C) + *(f32 *)(cfg + 0x40) * ((f32)rand() / F);
    step = *(f32 *)(cfg + 0x44) + *(f32 *)(cfg + 0x48) * ((f32)rand() / F);
    step = (step - pos) / (f32)*(s32 *)(e + 4);
    *(f32 *)(e + 0x40) = step;
    step = step * *(f32 *)(d + 0xC);
    pos = pos * *(f32 *)(d + 0xC);
    Mtx_StoreIdentity(ident);

    p = *(u8 **)e;
    if (p != 0) {
        for (;;) {
            *(u32 *)p |= 1;
            if (cfg[1] == 2) {
                Vec4_Set(dir, 0.0f, -1.0f, 0.0f, 1.0f);
                ra = rand();
                rb = rand();
                *(f32 *)(dir + 0) = *(f32 *)(dir + 0) + *(f32 *)(cfg + 0x58) * ((f32)ra / F - (f32)rb / F);
                ra = rand();
                rb = rand();
                *(f32 *)(dir + 8) = *(f32 *)(dir + 8) + *(f32 *)(cfg + 0x58) * ((f32)ra / F - (f32)rb / F);
                Vec3_Normalize(dir, dir);
            } else if (cfg[1] == 3) {
                func_00129C28(dir, d + 0x20);
            } else {
                Vec4_Set(dir, 0.0f, 0.0f, 1.0f, 1.0f);
                Mtx_RotateX(mat, ident, *(f32 *)(e + 0x28));
                Mtx_RotateY(mat, mat, *(f32 *)(e + 0x2C));
                func_00129C50(dir, mat, dir);
            }
            *(f32 *)(p + 0xC) = pos;
            func_00129BD0(p + 0x20, dir, pos);
            *(f32 *)(p + 0x2C) = 1.0f;

            if (idx == 0) {
                Vec4_Set(p + 0x30, 0.0f, 0.0f, 0.0f, 1.0f);
                *(f32 *)(p + 0x10) = 0.0f;
            } else {
                Vec3_Sub(vecT, p + 0x20, prev);
                *(f32 *)(vecT + 0xC) = 1.0f;
                len = func_00129CD8(vecT, vecT);
                len = __builtin_sqrtf(__builtin_fabsf(len));
                *(f32 *)(p + 0x10) = len * *(f32 *)(cfg + 0x54);
                ra = rand();
                rb = rand();
                *(f32 *)(p + 0x30) = *(f32 *)(p + 0x10) * ((f32)ra / F - (f32)rb / F);
                ra = rand();
                rb = rand();
                *(f32 *)(p + 0x34) = *(f32 *)(p + 0x10) * ((f32)ra / F - (f32)rb / F);
                ra = rand();
                rb = rand();
                *(f32 *)(p + 0x3C) = 1.0f;
                *(f32 *)(p + 0x38) = *(f32 *)(p + 0x10) * ((f32)ra / F - (f32)rb / F);
            }
            func_00129C28(prev, p + 0x20);

            *(f32 *)(p + 4) = *(f32 *)(cfg + 0x28) + *(f32 *)(cfg + 0x2C) * ((f32)rand() / F);
            a = *(f32 *)(cfg + 0x28) + *(f32 *)(cfg + 0x2C) * ((f32)rand() / F);
            *(f32 *)(p + 8) = a;
            if (idx == 0 || *(s32 *)(p + 0x60) == 0) {
                *(f32 *)(p + 8) = a * D_00384F70;
                *(f32 *)(p + 4) = *(f32 *)(p + 4) * D_00384F70;
            }
            func_00129C28(p + 0x50, e + 0x80);

            ang = *(f32 *)(e + 0x28) + *(f32 *)(e + 0x30);
            *(f32 *)(e + 0x28) = ang;
            if (D_00384F68 <= ang) {
                *(f32 *)(e + 0x28) = ang - D_00384F64;
            } else if (ang <= D_00384F6C) {
                *(f32 *)(e + 0x28) = ang + D_00384F64;
            }
            ang = *(f32 *)(e + 0x2C) + *(f32 *)(e + 0x34);
            *(f32 *)(e + 0x2C) = ang;
            if (D_00384F68 <= ang) {
                *(f32 *)(e + 0x2C) = ang - D_00384F64;
            } else if (ang <= D_00384F6C) {
                *(f32 *)(e + 0x2C) = ang + D_00384F64;
            }

            pos = pos + step;
            idx++;
            p = *(u8 **)(p + 0x60);
            if (p == 0) {
                break;
            }
        }
    }
    func_00129C38(e + 0x60, vecT);
}
