#include "common.h"

s32 BtlObjXf_Update(void *arg0);
void BtlAnim_SetBlend(f32, void *);
f32 BtlCharApi_GetHeight(s32);
f32 BtlUtil_WrapAngle(f32);
void func_001F9FB0(void *, s32);
s32 func_001FA0A0(void *, s32, s32);
void func_001FA360(f32, void *);
void func_001FA380(f32, void *);
void func_001FC3B0(f32, f32, f32, f32, f32, f32, void *, void *, void *, void *, void *, void *, void *, s32,
                   s32, s32, s32, s32, s32);
void func_00206958(void *, s64);
void func_00208DE8(s32, void *, s32);
f32 func_00210D50(void *);
void func_00210F30(void *, void *, s32);
s32 func_00211310(void *, s32, s32);
void func_002113C0(void *, s32, s32, s32);
f32 func_00212970(void);
void func_00215068(f32, f32, void *, s32, s32);
void func_00215E88(f32, void *, s32);
void func_00216208(f32, f32, void *);
void func_00216678(void *);
s32 func_002174B8(void *);
void sceVu0InterVector(f32, void *, void *, void *);
extern u8 D_002C3630[] __attribute__((section(".data")));
extern f32 D_00385E30;
extern f32 D_00385E34;
extern f32 D_00385E38;
extern f32 D_00385E3C;
extern f32 D_00385E40;
extern f32 D_00385E44;
extern f32 D_00385E48;
extern f32 D_00385E4C;
extern f32 D_00385E50;
extern f32 D_00385E54;
extern f32 D_00385E58;
extern f32 D_00385E5C;
extern f32 D_00385E60;

#define F32AT(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define S32AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

void func_0021E0D0(void *arg0) {
    u8 sp[0xA0];
    s32 v;
    s32 a1v;
    f32 f20;
    f32 f21;
    f32 f12;
    f32 f14;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 h;
    f32 t;
    u8 *s0;
    s32 r;

    v = BtlObjXf_Update(arg0);
    f20 = D_00385E30;
    if (v < 0x47) {
        if (v < 0x43) {
            /* v == 0 or v == 0x32: f20 = 0, func_001F9FB0(arg0, 1) */
            if (v == 0 || v == 0x32) {
                f20 = 0.0f;
                func_001F9FB0(arg0, 1);
            }
            goto after_block;
        }
    } else if (!(v >= 0x4C) && v != 0x47) {
        /* 0x48..0x4B fall into the block below */
    } else {
        goto after_block;
    }

    /* block B2: v in [0x43,0x46] or [0x48,0x4B] */
    func_001FA360(4.0f, arg0);
    func_001FA380(2.0f, arg0);
    r = func_002174B8(arg0);
    if (r != -1) {
        func_001F9FB0(arg0, 0);
    } else {
        a1v = (func_00211310(arg0, 0, 2) == 0) ? 0 : 0x32;
        if (func_001FA0A0(arg0, a1v, 0) != 0) {
            BtlAnim_SetBlend(D_00385E34, arg0);
        }
    }

after_block:
    f21 = 0.5f;
    func_00215068(D_00385E38, f21, arg0, 1, 0xC);
    func_00215E88(D_00385E3C, arg0, 2);
    func_00216208(f20, D_00385E40, arg0);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 0xD, 4, 1);
    func_00206958(arg0, (s64)0x8000 << 28);
    func_002113C0(arg0, 1, 0x800000, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
    func_00208DE8(S32AT(arg0, 0x1534), sp + 0x30, 3);
    func_00210F30(arg0, sp + 0x40, 3);
    sceVu0InterVector(f21, sp + 0x50, sp + 0x30, sp + 0x40);
    f0 = BtlCharApi_GetHeight(S32AT(arg0, 0x1534)) * 1.5f;
    f20 = 1.5f;
    h = f0;
    F32AT(sp, 0x60) = h;
    t = func_00210D50(arg0) * 1.5f;
    f1 = t;
    F32AT(sp, 0x64) = f1;
    if (!(f1 < h)) {
        f20 = f1;
    }

    if (S32AT(arg0, 0x9BC) != 0) {
        if (S32AT(arg0, 0x8CC) != 0) {
            f0 = F32AT(arg0, 0x8D8) - D_00385E5C;
            F32AT(arg0, 0x8D8) = f0;
            if (f0 < D_00385E60) {
                F32AT(arg0, 0x8D8) = D_00385E60;
            }
        } else {
            f0 = func_00212970();
            F32AT(arg0, 0x8D0) = f0 * D_00385E4C - D_00385E50;
            f0 = func_00212970();
            F32AT(arg0, 0x8D4) = f0 * D_00385E54 - D_00385E58;
            f0 = func_00212970();
            F32AT(arg0, 0x8D8) = f0 * 0.5f + 1.0f;
        }
        f12 = F32AT(arg0, 0x8D0);
        f14 = F32AT(arg0, 0x8D4);
        f0 = F32AT(arg0, 0x8D8);
        f20 = f20 * f0;
    } else {
        f0 = BtlUtil_WrapAngle(F32AT(arg0, 0x9B8) + D_00385E44);
        f14 = D_00385E48;
        F32AT(arg0, 0x9B8) = f0;
        f12 = f0;
    }

    func_001FC3B0(f12, 0.0f, f14, 0.0f, f20, 0.0f, arg0, sp + 0x50, D_002C3630, sp + 0x30, D_002C3630,
                  sp + 0x50, D_002C3630, -1, -1, -1, -1, 1, 0x47);
}
