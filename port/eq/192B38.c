#include "common.h"

void Vec3_Add(f32 *dst, f32 *a, f32 *b);
void Vec3_Sub(f32 *dst, f32 *a, f32 *b);
void Vec3_Cross(f32 *dst, f32 *a, f32 *b);
void Vec3_Normalize(f32 *dst, f32 *src);
void func_0012A360(f32 *dst, f32 *a, f32 *b, f32 s);
void func_00129BD0(f32 *src, f32 s, f32 *dst);
void Vec4_Set(f32 *v, f32 x, f32 y, f32 z, f32 w);
void Mtx_RotateZ(f32 *out, f32 *in, f32 angle);
void Mtx_RotateX(f32 *out, f32 *in, f32 angle);
void func_00129C50(f32 *out, f32 *mtx, f32 *in);
void func_00129B28(f32 *dst, f32 *a, f32 *b);
void func_00129D68(f32 *dst, f32 *src, f32 lo, f32 hi);
void func_00129C28(f32 *dst, f32 *src);
void func_00191B38(u8 *emitter, u8 *p);
extern s32 rand(void);
extern f32 D_00384C64, D_00384C68, D_00384C6C, D_00384C70, D_00384C74, D_00384C78;

#define F(p, off) (*(f32 *)((p) + (off)))
#define RANGE(q) (F(q, 0x10) + F(q, 0x14) * ((f32)rand() / D_00384C68))

void func_00192B38(u8 *e, u8 *env) {
    f32 mtx[16];
    f32 tmp[4];
    u8 *desc;
    u8 *p;
    u8 *next;
    u8 *s7, *s5, *s4, *s3, *s0, *s1;
    f32 a, b, d, dt, zero;
    u32 flags;
    s32 idx;

    desc = *(u8 **)(env + 0x38);
    p = *(u8 **)e;
    if (p == NULL) {
        return;
    }
    dt = 1.0f;
    zero = 0.0f;
    while (1) {
        if (!(F(p, 8) < F(p, 0xC))) {
            func_00191B38(e, p);
            *(u32 *)p = 0;
            *(s32 *)(e + 0x68) = *(s32 *)(e + 0x68) - 1;
            next = *(u8 **)(p + 0x140);
            goto advance;
        }
        s7 = p + 0xC0;
        s5 = p + 0xB0;
        s4 = p + 0xA0;
        Vec3_Add((f32 *)s7, (f32 *)s4, (f32 *)s5);
        Vec3_Normalize((f32 *)s7, (f32 *)s7);
        s0 = p + 0x70;
        s1 = p + 0x80;
        s3 = p + 0x60;
        func_0012A360((f32 *)s0, (f32 *)s7, (f32 *)s0, F(p, 0x24));
        Vec3_Add((f32 *)s1, (f32 *)s3, (f32 *)s0);
        s0 = p + 0x100;
        Vec3_Add((f32 *)(p + 0x90), (f32 *)s1, (f32 *)(env + 0x10));
        Vec3_Add((f32 *)s5, (f32 *)s5, (f32 *)s0);
        a = F(p, 0x4C);
        s1 = p + 0xD0;
        if (zero < a || a < zero) {
            a = F(p, 0x48) + a;
            F(p, 0x48) = a;
            if (D_00384C6C < a) {
                b = a - D_00384C64;
                F(p, 0x48) = b;
            } else if (a < D_00384C70) {
                b = a + D_00384C64;
                F(p, 0x48) = b;
            }
            Vec4_Set((f32 *)s3, 0.0f, -F(p, 0x5C), 0.0f, 1.0f);
            Mtx_RotateZ(mtx, (f32 *)(e + 0x130), F(p, 0x48));
            func_00129C50((f32 *)s3, mtx, (f32 *)s3);
            func_00129C50((f32 *)s3, (f32 *)(e + 0x170), (f32 *)s3);
            Vec4_Set((f32 *)s4, 0.0f, 0.0f, 1.0f, 1.0f);
            Mtx_RotateX(mtx, (f32 *)(e + 0x130), F(p, 0x44));
            Mtx_RotateZ(mtx, mtx, F(p, 0x48));
            func_00129C50((f32 *)s4, mtx, (f32 *)s4);
            func_00129C50((f32 *)s4, (f32 *)(e + 0x170), (f32 *)s4);
            Vec4_Set((f32 *)s5, 0.0f, 0.0f, 0.0f, 1.0f);
            Vec3_Cross((f32 *)s1, (f32 *)s3, (f32 *)s4);
            Vec3_Normalize((f32 *)s1, (f32 *)s1);
            Vec3_Normalize(tmp, (f32 *)s3);
            Vec3_Sub((f32 *)s0, (f32 *)(env + 0x20), tmp);
            F(p, 0x10C) = 1.0f;
            Vec3_Normalize((f32 *)s0, (f32 *)s0);
            func_00129BD0((f32 *)s0, *(f32 *)(e + 0xE0), (f32 *)s0);
        }
        flags = *(u32 *)p;
        if (!(flags & 2)) {
            if (F(desc, 0xC) <= F(p, 8)) {
                *(s32 *)(p + 0x12C) = 0;
                flags |= 2;
                *(u32 *)p = flags;
            }
        }
        if (!(flags & 4)) {
            if (F(p, 0x14) <= F(p, 8)) {
                d = F(p, 0xC) - F(p, 8);
                flags |= 4;
                *(u32 *)p = flags;
                F(p, 0x12C) = (-F(p, 0x11C)) / d;
            }
        }
        s0 = p + 0x110;
        if (!(flags & 8)) {
            if (F(p, 0x10) <= F(p, 8)) {
                d = F(p, 0xC) - F(p, 8);
                F(p, 0x28) = (RANGE(e + 0x8C) * F(env, 4) - F(p, 0x24)) / d;
                F(p, 0x30) = (RANGE(e + 0xA4) * F(env, 4) - F(p, 0x2C)) / d;
                F(p, 0x38) = (RANGE(e + 0xBC) * F(env, 4) - F(p, 0x34)) / d;
                a = RANGE(e + 0xF4);
                F(p, 0x54) = a;
                flags = *(u32 *)p;
                if (flags & 0x20) {
                    F(p, 0x54) = -a;
                }
                *(u32 *)p = flags | 8;
                s0 = p + 0x110;
            }
        }
        func_00129B28((f32 *)s0, (f32 *)s0, (f32 *)(p + 0x120));
        func_00129D68((f32 *)s0, (f32 *)s0, 0.0f, 255.0f);
        a = F(p, 0x2C) + F(p, 0x30);
        b = F(p, 0x24) + F(p, 0x28);
        F(p, 0x2C) = a;
        F(p, 0x24) = b;
        if (a < zero) {
            F(p, 0x2C) = zero;
        }
        a = F(p, 0x34) + F(p, 0x38);
        F(p, 0x34) = a;
        if (a < zero) {
            F(p, 0x34) = zero;
        }
        a = F(p, 0x50) + F(p, 0x54);
        F(p, 0x50) = a;
        if (D_00384C74 < a) {
            F(p, 0x50) = a - D_00384C64;
        } else if (a < D_00384C78) {
            F(p, 0x50) = a + D_00384C64;
        }
        d = *(f32 *)(e + 0xD4) + F(p, 0x20) * (F(p, 0x18) / F(p, 0x1C));
        F(p, 0x40) = F(p, 0x34) * d;
        F(p, 0x3C) = F(p, 0x2C) * d;
        func_00129C28((f32 *)(p + 0xE0), (f32 *)s7);
        func_00129C28((f32 *)(p + 0xF0), (f32 *)s1);
        flags = *(u32 *)p;
        if (flags & 0x10) {
            a = F(p, 0x18) - dt;
            F(p, 0x18) = a;
            if (a <= zero) {
                *(u32 *)(p + 0x18) = 0;
                *(u32 *)p = flags & ~0x10u;
            }
        } else {
            a = F(p, 0x18) + dt;
            F(p, 0x18) = a;
            if (F(p, 0x1C) <= a) {
                *(u32 *)p = flags | 0x10;
                F(p, 0x18) = F(p, 0x1C);
            }
        }
        if (*(u32 *)(e + 0x60) & 0x20) {
            idx = *(u8 *)(p + 5);
            F(p, 0x130) = (f32)(idx % *(s32 *)(desc + 0x14)) * F(e, 0x1C0);
            F(p, 0x134) = F(p, 0x130) + F(e, 0x1C0);
            F(p, 0x138) = (f32)(idx / *(s32 *)(desc + 0x14)) * F(e, 0x1C4);
            F(p, 0x13C) = F(p, 0x138) + F(e, 0x1C4);
            a = F(p, 0x58) + (f32)rand() / D_00384C68;
            F(p, 0x58) = a;
            if (F(desc, 0x1C) <= a) {
                F(p, 0x58) = a - F(desc, 0x1C);
                *(u8 *)(p + 5) = (u8)(s32)((f32)*(u8 *)(p + 5) + dt);
                if (!(*(u8 *)(p + 5) < *(s32 *)(e + 0x1BC))) {
                    *(u8 *)(p + 5) = 0;
                }
            }
        }
        F(p, 8) = F(p, 8) + dt;
        next = *(u8 **)(p + 0x140);
advance:
        p = next;
        if (p == NULL) {
            break;
        }
    }
}
