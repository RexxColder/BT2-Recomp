#include "common.h"

/* 0x001E8D30: initialises one effect particle (ctx+0x38, 0x190 bytes) from a spawn request (req): picks random
 * values inside the ranges of the effect description (req[0]) and of the spawn box (req[1]), builds the three-key
 * ramps (start, mid, end) for scale / colour channels and the initial direction. */
f32 Rand_FloatRange(f32 lo, f32 hi);
s32 Rand_IntRange(s32 lo, s32 hi);
void func_001EA610(u8 *obj, u8 *pack, s32 a, s32 b);
void func_00129D68(u8 *dst, u8 *src, f32 lo, f32 hi);
void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
void sceVu0DivVectorXYZ(u8 *dst, u8 *src, f32 d);
void func_00129BD0(u8 *dst, u8 *src, f32 s);
void func_00129C28(u8 *dst, u8 *src);
f32 EftMath_WrapAngle(f32 a);
f32 cosf(f32 a);
f32 sinf(f32 a);
void Vec3_Normalize(u8 *dst, u8 *src);
s32 rand(void);

extern f32 D_003856C4;

/* three keys v0 -> v1 -> v2; the middle key is the average of the ends when avg is set */
static void ramp3(f32 *dst, f32 v0, f32 v1, f32 v2, s32 avg, f32 t1, f32 t2) {
    dst[0] = v0;
    if (avg) {
        v1 = (v2 + v0) * 0.5f;
    }
    dst[1] = (v1 - v0) / t1;
    dst[2] = (v2 - v1) / t2;
}

void func_001E8D30(u8 *ctx, u8 *req) {
    u8 sp[0x20];
    u8 *obj = *(u8 **)(ctx + 0x38);
    u8 *desc = *(u8 **)(req + 0);
    f32 *box = *(f32 **)(req + 4);
    f32 *fd = (f32 *)desc;
    f32 life, tMid, tEnd;
    f32 a, b, c, d;
    f32 sc = D_003856C4;
    f32 cap;
    s32 i;
    s32 n;
    s32 *p;
    s32 v;
    u32 fl;
    f32 *vec = (f32 *)(sp + 0x10);

    __builtin_memset(sp, 0, 8);
    __builtin_memset(obj, 0, 0x190);
    *(u32 *)(obj + 0x00) = *(u32 *)(req + 0);
    *(u32 *)(obj + 0x120) = *(u32 *)(req + 0x38);
    *(u8 *)(obj + 0x126) = *(u8 *)(req + 0x3C);

    life = Rand_FloatRange(fd[0], fd[0] + fd[1]) * 30.0f;
    *(f32 *)(obj + 0x10C) = life;
    tMid = life * fd[6];
    tEnd = life * (1.0f - fd[6]);

    /* spin / scale ramp */
    *(f32 *)(obj + 0xE0) = Rand_FloatRange(fd[31], fd[31] + fd[32]) * sc;
    a = Rand_FloatRange(fd[25], fd[25] + fd[28]) * sc;
    b = Rand_FloatRange(fd[26], fd[26] + fd[29]) * sc;
    c = Rand_FloatRange(fd[27], fd[27] + fd[30]) * sc;
    ramp3((f32 *)(obj + 0xE4), a, b, c, *(u32 *)(desc + 0x98) & 0x20000, tMid, tEnd);

    a = Rand_FloatRange(fd[13], fd[13] + fd[16]);
    b = Rand_FloatRange(fd[14], fd[14] + fd[17]);
    c = Rand_FloatRange(fd[15], fd[15] + fd[18]);
    ramp3((f32 *)(obj + 0xF0), a, b, c, *(u32 *)(desc + 0x98) & 0x4000, tMid, tEnd);

    a = Rand_FloatRange(fd[19], fd[19] + fd[22]);
    b = Rand_FloatRange(fd[20], fd[20] + fd[23]);
    c = Rand_FloatRange(fd[21], fd[21] + fd[24]);
    ramp3((f32 *)(obj + 0xC8), a, b, c, *(u32 *)(desc + 0x98) & 0x100, tMid, tEnd);

    a = Rand_FloatRange(fd[7], fd[7] + fd[10]) * 0.5f;
    b = Rand_FloatRange(fd[8], fd[8] + fd[11]) * 0.5f;
    c = Rand_FloatRange(fd[9], fd[9] + fd[12]) * 0.5f;
    ramp3((f32 *)(obj + 0xFC), a, b, c, *(u32 *)(desc + 0x98) & 0x800, tMid, tEnd);

    *(u8 **)(obj + 0x128) = *(u8 **)(req + 8);
    *(s32 *)(obj + 0x118) = *(s32 *)(req + 0x34);
    *(s32 *)(obj + 0x11C) = *(s32 *)(req + 0x34) + 1;
    if (*(s32 *)(*(u8 **)(req + 8) + 0x100) < 2) {
        *(s32 *)(obj + 0x11C) = *(s32 *)(req + 0x34);
    }
    if (*(s32 *)(*(u8 **)(obj + 0x128) + 0x100) > 0) {
        p = (s32 *)(obj + 0x118);
        i = 0;
        do {
            n = *p;
            p++;
            i++;
            func_001EA610(obj, *(u8 **)(req + 8), n, n);
        } while (i < *(s32 *)(*(u8 **)(obj + 0x128) + 0x100));
    }

    /* start position and direction */
    *(f32 *)(obj + 0x50) = Rand_FloatRange(box[0], box[0] + box[4]);
    *(f32 *)(obj + 0x54) = Rand_FloatRange(box[1], box[1] + box[5]);
    a = Rand_FloatRange(box[2], box[2] + box[6]);
    *(s32 *)(obj + 0x5C) = 0;
    *(f32 *)(obj + 0x58) = a;
    vec[0] = Rand_FloatRange(box[8], box[8] + box[12]);
    vec[1] = Rand_FloatRange(box[9], box[9] + box[13]);
    vec[2] = Rand_FloatRange(box[10], box[10] + box[14]);
    vec[3] = 0.0f;
    func_00129D68(obj + 0x50, obj + 0x50, 0.0f, 255.0f);
    func_00129D68((u8 *)vec, (u8 *)vec, 0.0f, 255.0f);
    Vec3_Sub(obj + 0x60, (u8 *)vec, obj + 0x50);
    sceVu0DivVectorXYZ(obj + 0x60, obj + 0x60, *(f32 *)(obj + 0x10C));
    func_00129BD0(obj + 0x60, obj + 0x60, 1.0f);

    cap = Rand_FloatRange(box[3], box[3] + box[7]);
    if (255.0f < cap) {
        cap = 255.0f;
    }
    *(f32 *)(obj + 0xD4) = cap / (*(f32 *)(obj + 0x10C) * fd[4]);
    *(f32 *)(obj + 0xD8) = -cap / (*(f32 *)(obj + 0x10C) * (1.0f - fd[5]));

    *(f32 *)(obj + 0xB4) = 0.0f;
    *(f32 *)(obj + 0xC4) = *(f32 *)(req + 0x30);
    *(f32 *)(obj + 0xB0) = 0.0f;
    *(f32 *)(obj + 0xB8) = Rand_FloatRange(fd[33], fd[33] + fd[34]);
    *(f32 *)(obj + 0xBC) = 1.0f;
    v = Rand_IntRange(*(s32 *)(desc + 0x8C), *(s32 *)(desc + 0x8C) + *(s32 *)(desc + 0x90));
    *(s32 *)(obj + 0x110) = v;
    if (v < 3) {
        *(s32 *)(obj + 0x110) = 3;
    }
    *(f32 *)(obj + 0xC0) = Rand_FloatRange(fd[2], fd[2] + fd[3]) * 30.0f;
    func_00129C28(obj + 0x90, req + 0x10);
    func_00129C28(obj + 0x80, req + 0x20);

    *(f32 *)(obj + 0x70) = cosf(EftMath_WrapAngle(*(f32 *)(obj + 0xE0))) * *(f32 *)(obj + 0xF0);
    *(f32 *)(obj + 0x74) = sinf(EftMath_WrapAngle(*(f32 *)(obj + 0xE0))) * *(f32 *)(obj + 0xF0);
    *(f32 *)(obj + 0x7C) = 1.0f;
    Vec3_Normalize(obj + 0xA0, obj + 0x70);
    *(f32 *)(obj + 0xDC) = 1.0f;

    fl = *(u32 *)(desc + 0x98);
    if (fl & 0x80000) {
        *(f32 *)(obj + 0xDC) = -1.0f;
        fl = *(u32 *)(desc + 0x98);
    }
    if (fl & 0x100000) {
        if ((rand() & 1) == 0) {
            *(f32 *)(obj + 0xDC) = -1.0f;
        }
    }
    *(u32 *)(obj + 0x180) = 0;
    *(u32 *)(obj + 0x184) = 0;
    *(u16 *)(obj + 0x124) = *(u16 *)(obj + 0x124) | 0x101;
    if (*(u32 *)(desc + 0x98) & 0x200000) {
        *(u16 *)(obj + 0x124) = *(u16 *)(obj + 0x124) & 0xFEFF;
    }
    fl = *(u32 *)(desc + 0x98);
    if (fl & 0x10) {
        *(u16 *)(obj + 0x124) = *(u16 *)(obj + 0x124) | 0x40;
        fl = *(u32 *)(desc + 0x98);
    }
    if (fl & 0x20) {
        if ((rand() & 1) == 0) {
            *(u16 *)(obj + 0x124) = *(u16 *)(obj + 0x124) | 0x40;
        }
    }
}
