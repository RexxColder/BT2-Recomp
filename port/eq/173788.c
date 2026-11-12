#include "common.h"

/* 0x00173788: per-frame update of an effect shot task (state byte at obj+1: 0..5). */
s32 BtlScene_IsCharStopped(s32 chr);
s32 EftShot_TestBits(s32 chr, s32 bits);
void Vec4_Set(u8 *v, f32 x, f32 y, f32 z, f32 w);
void Mtx_StoreIdentity(u8 *m);
void Mtx_RotateX(u8 *dst, u8 *src, f32 ang);
void Mtx_RotateY(u8 *dst, u8 *src, f32 ang);
f32 Mathf_Asin(f32 x);
f32 EftMath_WrapAngle(f32 a);
f32 atan2f(f32 y, f32 x);
f32 cosf(f32 a);
f32 sinf(f32 a);
f32 Rand_FloatRange(f32 lo, f32 hi);
void Vec3_Add(u8 *dst, u8 *a, u8 *b);
s32 BtlTask_SetDead(u8 *task);
u8 *func_001F3758(void *a0);
void func_00152960(s32 chr, u8 *s);
void func_00152530(u8 *s, u8 *p);
void func_00208DE8(s32 chr, u8 *out, s32 idx);
void func_00129C28(u8 *dst, u8 *src);
void func_00129C38(u8 *dst, u8 *src);
void func_0012D3A0(u8 *a, u8 *b, s32 chr);
f32 func_0020A068(s32 chr);
void func_0012D488(u8 *s, u8 *out, u8 *p, s32 chr);
void func_00129C50(u8 *dst, u8 *mtx, u8 *src);
void func_00129BD0(u8 *dst, u8 *src, f32 s);
void func_0012D5D8(u8 *a, u8 *b, u8 *c, s32 chr, f32 f0, f32 f1);
f32 func_00173100(u8 *a, u8 *b, u8 *c, s32 chr, f32 f0, f32 f1);
void func_00151FB0(u8 *p);
void func_00173538(s32 chr, u8 *task, u8 *p, s32 z);
s32 func_00152200(u8 *a, u8 *b);
void func_00152930(u8 *a, u8 *b);
void func_00173370(u8 *task);

extern f32 D_003848F4;

s32 func_00173788(u8 *task) {
    u8 sp[0x80];   /* tamano de locales del original (antes 0x78) */
    u8 *vec = sp;
    u8 *vec2 = sp + 0x10;
    u8 *mat = sp + 0x20;
    u8 *tmp = sp + 0x60;
    s32 *advance = (s32 *)(sp + 0x70);
    u8 *ctx;
    u8 *shot;
    u8 *fp;
    u8 *p;
    s32 stopped;
    s32 chr;
    s32 alive;
    u32 flags;

    fp = *(u8 **)(func_001F3758(task) + 0x38);
    ctx = *(u8 **)(task + 0x38);
    shot = *(u8 **)(ctx + 0xB0);
    __builtin_memset(vec2, 0, 0x10);
    __builtin_memset(mat, 0, 0x40);
    *advance = 0;
    stopped = BtlScene_IsCharStopped(*(s32 *)shot);
    if (stopped != 0) {
        return stopped;
    }
    func_00152960(*(s32 *)shot, shot);
    func_00152530(shot, ctx + 0x860);

    if ((*(u32 *)ctx & 0x80) == 0) {
        if (EftShot_TestBits(*(s32 *)shot, 2) != 0) {
            task[1] = 0;
            *(u32 *)ctx |= 0x80;
        } else if (EftShot_TestBits(*(s32 *)shot, 4) != 0) {
            task[1] = 2;
            *(u32 *)ctx |= 0x80;
        }
    }

    if ((*(u32 *)ctx & 0x80) != 0 && task[1] < 6) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)shot, 2) != 0) {
                s32 idx = *(s32 *)(ctx + 0x870);
                *(s32 *)(ctx + 4) = idx;
                func_00208DE8(*(s32 *)shot, vec, idx);
                func_00129C28(ctx + 0x40, vec);
                func_0012D3A0(ctx + 0x30, ctx + 0x40, *(s32 *)shot);
                task[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            *advance = 1;
            break;
        case 2: {
            f32 v = func_0020A068(*(s32 *)shot);
            *(f32 *)(ctx + 0x1C) = v;
            *(f32 *)(ctx + 0x18) = *(f32 *)(ctx + 0x14) * (v + 1.0f);
            func_00208DE8(*(s32 *)shot, vec, *(s32 *)(ctx + 4));
            func_00129C28(ctx + 0x40, vec);
            if (EftShot_TestBits(*(s32 *)shot, 0x40) != 0) {
                s32 idx = *(s32 *)(ctx + 0x9B0);
                *(s32 *)(ctx + 0xC) = idx;
                func_00208DE8(*(s32 *)shot, vec, idx);
                func_00129C28(ctx + 0x60, vec);
                *(u32 *)ctx |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)shot, 4) != 0) {
                f32 ax;
                f32 ay;
                s32 idx;
                Vec4_Set(ctx + 0x30, 0.0f, 0.0f, 1.0f, 1.0f);
                idx = *(s32 *)(ctx + 0x8B0);
                *(u32 *)ctx |= 0x10;
                *(s32 *)(ctx + 8) = idx;
                func_00208DE8(*(s32 *)shot, vec, idx);
                func_00129C28(ctx + 0x50, vec);
                func_00129C28(ctx + 0x70, ctx + 0x50);
                func_00129C28(ctx + 0x80, ctx + 0x70);
                func_00208DE8(*(s32 *)shot, ctx + 0x90, 0x11);
                func_0012D488(shot, vec2, ctx + 0x80, *(s32 *)shot);
                Mtx_StoreIdentity(mat);
                ax = EftMath_WrapAngle(Mathf_Asin(-*(f32 *)(sp + 0x14)));
                ay = EftMath_WrapAngle(atan2f(*(f32 *)(sp + 0x10), *(f32 *)(sp + 0x18)));
                Mtx_RotateX(mat, mat, ax);
                Mtx_RotateY(mat, mat, ay);
                func_00129C50(ctx + 0x30, mat, ctx + 0x30);
                func_00129BD0(ctx + 0xA0, ctx + 0x30, *(f32 *)(ctx + 0x10));
                task[1] = 3;
            }
            break;
        }
        case 4: {
            u8 *obj2;
            u8 *dir = ctx + 0x30;
            u8 *pos = ctx + 0x80;
            u8 *vel = ctx + 0xA0;
            f32 lim;
            __builtin_memset(tmp, 0, 0x10);
            func_00129C28(ctx + 0x90, pos);
            obj2 = *(u8 **)(*(u8 **)(ctx + 0xB0) + 0x20);
            if ((*(u32 *)(obj2 + 0x30) & 2) != 0) {
                /* nothing */
            } else if ((*(u32 *)ctx & 0x20) != 0) {
                func_00129C38(pos, task + 0x10);
            } else {
                f32 dist;
                lim = *(f32 *)(obj2 + 0x18);
                if (0.0f < lim) {
                    func_0012D5D8(dir, pos, dir, *(s32 *)shot, *(f32 *)(ctx + 0x10), lim);
                    func_00129BD0(vel, dir, *(f32 *)(ctx + 0x10));
                }
                dist = func_00173100(dir, pos, dir, *(s32 *)shot, *(f32 *)(ctx + 0x10), 1.0f);
                if (10.0f < dist) {
                    s32 n = (s32)dist;
                    if (n % 3 == 0) {
                        f32 ang;
                        f32 rad;
                        f32 ax;
                        f32 ay;
                        ang = EftMath_WrapAngle(Rand_FloatRange(0.0f, D_003848F4));
                        rad = Rand_FloatRange(2.0f, 3.5f);
                        *(f32 *)(tmp + 0) = cosf(ang) * rad;
                        *(f32 *)(tmp + 4) = -sinf(ang) * rad;
                        *(s32 *)(tmp + 8) = 0;
                        *(f32 *)(tmp + 12) = 1.0f;
                        Mtx_StoreIdentity(mat);
                        ax = EftMath_WrapAngle(Mathf_Asin(-*(f32 *)(ctx + 0x34)));
                        ay = EftMath_WrapAngle(atan2f(*(f32 *)dir, *(f32 *)(ctx + 0x38)));
                        Mtx_RotateX(mat, mat, ax);
                        Mtx_RotateY(mat, mat, ay);
                        func_00129C50(tmp, mat, tmp);
                    }
                } else {
                    Vec4_Set(tmp, 0.0f, 0.0f, 0.0f, 1.0f);
                }
                func_00129BD0(vel, dir, *(f32 *)(ctx + 0x10));
                Vec3_Add(vel, vel, tmp);
                Vec3_Add(pos, pos, vel);
            }
            func_00208DE8(*(s32 *)shot, vec, *(s32 *)(ctx + 8));
            func_00129C28(ctx + 0x50, vec);
            if (EftShot_TestBits(*(s32 *)shot, 8) != 0) {
                *(u32 *)ctx |= 9;
                task[1] = 5;
            }
            break;
        }
        }
    }

    chr = *(s32 *)shot;
    p = ctx + 0xB4;
    if (EftShot_TestBits(chr, 0x80) != 0) {
        flags = *(u32 *)ctx;
        if ((flags & 8) == 0) {
            flags |= 4;
        }
        *(u32 *)ctx = flags | 1;
    }
    func_00151FB0(p);
    func_00173538(*(s32 *)shot, task, fp, 0);
    alive = func_00152200(fp, p) != 0;
    if (*advance != 0) {
        task[1] = task[1] + 1;
    }
    flags = *(u32 *)ctx;
    if (alive == 0 && (flags & 2) != 0) {
        return BtlTask_SetDead(task);
    }
    if ((flags & 1) != 0) {
        *(u32 *)ctx = flags | 2;
        return flags | 2;
    }
    if ((*(u32 *)(*(u8 **)(shot + 0x20) + 0x30) & 1) != 0 && (flags & 0x10) != 0) {
        func_00152930(fp, p);
        func_00173370(task);
    }
    return flags & 0x10;
}
