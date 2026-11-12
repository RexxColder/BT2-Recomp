#include "common.h"

/* 0x0018CBC8: initialise one effect particle (obj) from an emitter description (desc) and random ranges. */
f32 Rand_FloatRange(f32 lo, f32 hi);
s32 Rand_IntRange(s32 lo, s32 hi);
void Vec4_Set(u8 *v, f32 x, f32 y, f32 z, f32 w);
void func_00129C28(u8 *dst, u8 *src);
void func_0018DE48(u8 *v, f32 lo, f32 hi);
void func_0018DE18(u8 *v, f32 lo, f32 hi);
void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
void sceVu0DivVectorXYZ(u8 *dst, u8 *src, f32 d);
void Mtx_StoreIdentity(u8 *m);
void Mtx_RotateZ(u8 *dst, u8 *src, f32 ang);
f32 sinf(f32 a);
f32 cosf(f32 a);
f32 EftMath_WrapAngle(f32 a);
void func_00129C50(u8 *dst, u8 *mtx, u8 *src);
void Vec3_Normalize(u8 *dst, u8 *src);
void func_00129BD0(u8 *dst, u8 *src, f32 s);
s32 rand(void);

extern f32 D_00384C08;
extern f32 D_00384C0C;
extern f32 D_00384C10;
extern f32 D_00384C14;

void func_0018CBC8(u8 *obj, u8 *desc, f32 *range, u8 *posA, u8 *posB, u8 *table, u8 count, u8 *cursor,
                   u32 base, u8 useBase) {
    u8 sp[0x90];
    u8 *vecA = sp + 0x20;
    u8 *mtx = sp + 0x40;
    u8 *axis = sp + 0x80;
    f32 *tmp = (f32 *)(sp + 0x20);
    f32 *ftmp = (f32 *)(sp + 0x30);
    f32 scale;
    f32 rx, ry, rz, r;
    f32 t0, t1;
    f32 *fd = (f32 *)desc;
    s32 allow;
    f32 ang;

    __builtin_memcpy(sp, posA, 8);
    __builtin_memcpy(sp + 8, posA + 8, 8);
    __builtin_memcpy(sp + 0x10, posB, 8);
    __builtin_memcpy(sp + 0x18, posB + 8, 8);

    rx = Rand_FloatRange(*(f32 *)(desc + 0x40), *(f32 *)(desc + 0x40) + *(f32 *)(desc + 0x44));
    ry = Rand_FloatRange(*(f32 *)(desc + 0x48), *(f32 *)(desc + 0x48) + *(f32 *)(desc + 0x4C));
    rz = Rand_FloatRange(*(f32 *)(desc + 0x50), *(f32 *)(desc + 0x50) + *(f32 *)(desc + 0x54));
    Vec4_Set(obj, rx, ry, rz, 1.0f);
    func_00129C28(obj + 0x10, sp);

    r = Rand_FloatRange(*(f32 *)(desc + 0x88), *(f32 *)(desc + 0x88) + *(f32 *)(desc + 0x8C));
    *(s32 *)(obj + 0xC8) = 0;
    *(f32 *)(obj + 0xB0) = r * D_00384C08;
    r = Rand_FloatRange(*(f32 *)(desc + 0x70), *(f32 *)(desc + 0x70) + *(f32 *)(desc + 0x74));
    *(s32 *)(obj + 0xF4) = 0;
    *(f32 *)(obj + 0xB4) = r;
    *(f32 *)(obj + 0xE0) = r;
    *(s32 *)(obj + 0xF8) = 0;
    r = Rand_FloatRange(*(f32 *)(desc + 0x58), *(f32 *)(desc + 0x58) + *(f32 *)(desc + 0x5C));
    *(f32 *)(obj + 0x60) = r * D_00384C08;
    r = Rand_FloatRange(*(f32 *)(desc + 0x60), *(f32 *)(desc + 0x60) + *(f32 *)(desc + 0x64));
    *(f32 *)(obj + 0x64) = r * D_00384C08;
    r = Rand_FloatRange(*(f32 *)(desc + 0x68), *(f32 *)(desc + 0x68) + *(f32 *)(desc + 0x6C));
    *(f32 *)(obj + 0x6C) = 1.0f;
    scale = *(f32 *)(obj + 0xE0) * 10.0f;
    *(f32 *)(obj + 0x68) = r * D_00384C0C;

    if (useBase) {
        *(u8 *)(obj + 0xF0) = (u8)(table[0] + base);
    } else {
        switch (desc[0xA9]) {
        case 0:
            *(u8 *)(obj + 0xF0) = table[0];
            break;
        case 1:
            *(u8 *)(obj + 0xF0) = table[Rand_IntRange(0, count - 1)];
            break;
        case 2: {
            s32 v;
            *(u8 *)(obj + 0xF0) = table[*cursor];
            v = *cursor + 1;
            *cursor = (u8)v;
            if ((s32)(count - 1) < (v & 0xFF)) {
                *cursor = 0;
            }
            break;
        }
        default:
            break;
        }
    }

    __builtin_memset(vecA, 0, 0x10);
    if (desc[0xAA] == 1) {
        *(u32 *)(obj + 0xEC) |= 0x100;
    } else if (desc[0xAA] == 2) {
        if ((rand() & 1) == 0) {
            *(u32 *)(obj + 0xEC) |= 0x100;
        }
    }

    *(f32 *)(obj + 0x40) = Rand_FloatRange(range[0], range[0] + range[4]);
    *(f32 *)(obj + 0x44) = Rand_FloatRange(range[1], range[1] + range[5]);
    r = Rand_FloatRange(range[2], range[2] + range[6]);
    *(f32 *)(obj + 0x4C) = 0.0f;
    *(f32 *)(obj + 0x48) = r;
    r = Rand_FloatRange(range[3], range[3] + range[7]);
    *(f32 *)(obj + 0xE4) = r / (scale * *(f32 *)(desc + 0x34));
    *(f32 *)(obj + 0xE8) = r / (scale * (1.0f - *(f32 *)(desc + 0x38)));
    func_0018DE48(obj + 0x40, 0.0f, 255.0f);
    func_0018DE18(obj + 0xE4, 0.0f, 255.0f);
    func_0018DE18(obj + 0xE8, 0.0f, 255.0f);

    tmp[0] = Rand_FloatRange(range[8], range[8] + range[12]);
    tmp[1] = Rand_FloatRange(range[9], range[9] + range[13]);
    tmp[2] = Rand_FloatRange(range[10], range[10] + range[14]);
    tmp[3] = 0.0f;
    func_0018DE48(vecA, 0.0f, 255.0f);
    Vec3_Sub(obj + 0x50, vecA, obj + 0x40);
    sceVu0DivVectorXYZ(obj + 0x50, obj + 0x50, scale);

    ftmp[0] = Rand_FloatRange(fd[1], fd[1] + fd[4]);
    ftmp[1] = Rand_FloatRange(fd[2], fd[2] + fd[5]);
    r = Rand_FloatRange(fd[3], fd[3] + fd[6]);
    *(f32 *)(obj + 0xD4) = 1.0f;
    t0 = ftmp[0];
    t1 = ftmp[1];
    ftmp[2] = r;
    *(f32 *)(obj + 0xD8) = (t1 - t0) / (scale * fd[15]);
    *(f32 *)(obj + 0xDC) = (r - t1) / (scale * (1.0f - fd[15]));
    r = Rand_FloatRange(fd[32], fd[32] + fd[33]);
    *(f32 *)(obj + 0xD0) = r * ftmp[0];
    *(f32 *)(obj + 0xCC) = r * ftmp[0];

    ftmp[0] = Rand_FloatRange(fd[7], fd[7] + fd[10]);
    ftmp[1] = Rand_FloatRange(fd[8], fd[8] + fd[11]);
    r = Rand_FloatRange(fd[9], fd[9] + fd[12]);
    *(f32 *)(obj + 0xBC) = 1.0f;
    t1 = ftmp[1];
    t0 = ftmp[0];
    ftmp[2] = r;
    *(f32 *)(obj + 0xC0) = (t1 - t0) / (scale * fd[15]);
    *(f32 *)(obj + 0xC4) = (r - t1) / (scale * (1.0f - fd[15]));
    r = Rand_FloatRange(fd[36], fd[36] + fd[37]);
    *(f32 *)(obj + 0xB8) = r * ftmp[0];

    if ((Rand_IntRange(0, 0x400) & 1) == 0) {
        *(f32 *)(obj + 0x60) = -*(f32 *)(obj + 0x60);
    }
    if ((Rand_IntRange(0, 0x400) & 1) == 0) {
        *(f32 *)(obj + 0x64) = -*(f32 *)(obj + 0x64);
    }
    if ((Rand_IntRange(0, 0x400) & 1) == 0) {
        *(f32 *)(obj + 0x68) = -*(f32 *)(obj + 0x68);
    }

    t0 = fd[34];
    allow = 1;
    if (t0 < 0.0f) {
        if (0.0f < t0 + fd[35]) {
            allow = 0;
        }
    }
    if (0.0f < t0) {
        if (t0 + fd[35] < 0.0f) {
            allow = 0;
        }
    }
    if (allow) {
        if ((Rand_IntRange(0, 0x400) & 1) == 0) {
            *(f32 *)(obj + 0xB0) = -*(f32 *)(obj + 0xB0);
        }
    }

    Mtx_StoreIdentity(mtx);
    Vec4_Set(axis, 0.0f, 0.0f, 1.0f, 1.0f);
    ang = Rand_FloatRange(fd[30], fd[30] + fd[31]) * D_00384C10;
    *(f32 *)(obj + 0x24) = 0.0f;
    *(f32 *)(obj + 0x20) = sinf(ang);
    *(f32 *)(obj + 0x2C) = 1.0f;
    *(f32 *)(obj + 0x28) = cosf(ang);
    ang = EftMath_WrapAngle(Rand_FloatRange(0.0f, 1.0f) * D_00384C14);
    Mtx_RotateZ(mtx, mtx, ang);
    func_00129C50(obj + 0x20, mtx, obj + 0x20);
    Vec3_Sub(obj + 0x30, axis, obj + 0x20);
    Vec3_Normalize(obj + 0x30, obj + 0x30);
    func_00129BD0(obj + 0x30, obj + 0x30, fd[38]);
}
