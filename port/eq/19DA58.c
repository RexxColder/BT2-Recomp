#include "common.h"

extern f32 D_00384D7C;
extern f32 D_00384D80;
extern f32 D_00384D84;
extern f32 D_00384D88;
extern f32 D_00384D8C;
extern f32 D_00384D90;
extern f32 D_00384D94;
extern f32 D_00384D98;
extern f32 D_00384D9C;
extern f32 D_00384DA0;
extern f32 D_00384DA4;
extern f32 D_00384DA8;
extern f32 D_00384DAC;
extern f32 D_00384DB0;
extern u8 D_00387800[];

extern f32 Rand_FloatRange(f32 lo, f32 hi);
extern s32 Rand_IntRange(s32 lo, s32 hi);
extern void Vec3_Add(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Scale(u8 *out, u8 *a, f32 s);
extern void func_00129C28(u8 *dst, s32 src);
extern f32 EftVolleyAim_Lerp(f32 farg0, f32 farg1, f32 farg2);
extern void func_001C1790(u8 *obj, u8 *p, s32 a2, s32 a3, s32 a4, u8 *tbl, s32 a6);
extern s32 func_001C15A0(u8 *obj, u8 *p, s32 start, s32 end, u8 *vec);
extern u8 *func_001C1560(u8 *obj, u8 *p, s16 start, s16 end, f32 val);
extern void func_001C1650(u8 *obj, u8 *p, s32 start, s32 end, f32 v0, f32 v1);
extern s32 func_001C15F8(u8 *obj, u8 *p, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_001C17F8(u8 *obj, u8 *p, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, f32 f0, f32 f1);

/* frame index of a segment start: truncation of the scaled position */
#define FRAME_FLOOR(x) ((s16)(s32)(x))
/* frame index of a segment end: rounds up when the truncation lost a fraction */
#define FRAME_CEIL(x) (((f32)FRAME_FLOOR(x) == (x)) ? FRAME_FLOOR(x) : (s16)(s32)((x) + 1.0f))

/* Effect emitter init: builds the keyframe tracks of the object from the config block. */
s32 func_0019DA58(u8 *obj, u8 *cfg, s32 arg2, u8 *dir, s32 arg4, s32 arg5, f32 scale, f32 fscale) {
    u8 sp[0x60];   /* tamano de locales del original (antes 0x40) */
    f32 rnd;
    f32 prev;
    f32 cur;
    f32 delta;
    f32 k;
    f32 vlo;
    f32 vhi;
    f32 sgn;
    f32 spread;
    f32 mul;
    s32 i;
    s32 size;
    s32 start;
    s32 end;
    s16 tmp;
    u8 *key;

    if (*(u16 *)(cfg + 2) & 0x100) {
        s32 sz = *(s16 *)(obj + 4);
        s32 n;
        s32 s0 = sz;
        n = (sz < 0 ? sz + 15 : sz) >> 4;
        func_001C1790(obj, obj + 0xC, 1, s0, n ? n : 1, D_00387800, 4);
        sz = *(s16 *)(obj + 4);
        n = (sz < 0 ? sz + 3 : sz) >> 2;
        func_001C1790(obj, obj + 0xD, 1, s0, n ? n : 1, D_00387800, 4);
    }

    if (dir != 0) {
        rnd = Rand_FloatRange(0.0f, 1.0f);
        prev = ((f32)*(s8 *)(cfg + 0x1A) + (f32)cfg[0x1B] * rnd) * scale * D_00384D7C;
        if (prev != 0.0f) {
            Vec3_Scale(sp, dir, prev);
            Vec3_Add(obj + 0x20, obj + 0x20, sp);
        }
        k = D_00384D80;
        key = cfg + 0x1C;
        for (i = 0; i < 3; i++) {
            cur = ((f32)*(s8 *)(cfg + 0x1D + 3 * i) + (f32)cfg[0x1E + 3 * i] * rnd) * scale * D_00384D84;
            delta = cur - prev;
            if (delta != 0.0f) {
                size = *(s16 *)(obj + 4);
                start = FRAME_FLOOR((f32)(size * key[-3]) * k);
                end = FRAME_CEIL((f32)(size * key[0]) * k);
                if (start != end) {
                    Vec3_Scale(sp + 0x10, dir, delta / (f32)(end - start + 1));
                    prev = cur;
                    func_001C15A0(obj, obj + 0x20, start, end, sp + 0x10);
                }
            }
            key += 3;
        }
    }

    /* scalar at +0x24 */
    rnd = Rand_FloatRange(0.0f, 1.0f);
    delta = ((f32)*(s8 *)(cfg + 0x26) + (f32)cfg[0x27] * rnd) * scale;
    cur = *(f32 *)(obj + 0x24) + delta;
    *(f32 *)(obj + 0x24) = cur;
    if (fscale != 0.0f) {
        fscale = fscale * ((f32)*(s8 *)(cfg + 0x12) * D_00384D88);
        *(f32 *)(obj + 0x24) = cur + cur * fscale;
    }
    k = D_00384D8C;
    prev = delta;
    key = cfg + 0x28;
    for (i = 0; i < 3; i++) {
        f32 fr;
        f32 val;
        cur = ((f32)*(s8 *)(cfg + 0x29 + 3 * i) + (f32)cfg[0x2A + 3 * i] * rnd) * scale;
        val = cur - prev;
        if (val != 0.0f) {
            size = *(s16 *)(obj + 4);
            start = FRAME_FLOOR((f32)(size * key[-3]) * k);
            end = FRAME_CEIL((f32)(size * key[0]) * k);
            if (start != end) {
                fr = val / (f32)(end - start + 1);
                if (fscale != 0.0f) {
                    f32 t = (f32)end / (f32)(s16)size;
                    f32 l = EftVolleyAim_Lerp((f32)*(s8 *)(cfg + 0x12), (f32)*(s8 *)(cfg + 0x13), t);
                    fscale = fscale * (l * k);
                    fr = fr + fr * fscale;
                }
                func_001C1560(obj, obj + 0x24, start, end, fr);
                prev = cur;
            }
        }
        key += 3;
    }

    /* scalar at +0x10 */
    rnd = Rand_FloatRange(0.0f, 1.0f);
    prev = ((f32)cfg[0x32] + (f32)cfg[0x33] * rnd) * scale;
    *(f32 *)(obj + 0x10) = prev;
    k = D_00384D90;
    key = cfg + 0x34;
    for (i = 0; i < 3; i++) {
        cur = ((f32)cfg[0x35 + 3 * i] + (f32)cfg[0x36 + 3 * i] * rnd) * scale;
        if (prev != cur) {
            size = *(s16 *)(obj + 4);
            start = FRAME_FLOOR((f32)(size * key[-3]) * k);
            end = FRAME_CEIL((f32)(size * key[0]) * k);
            if (start != end) {
                func_001C1560(obj, obj + 0x10, start, end, (cur - prev) / (f32)(end - start + 1));
                prev = cur;
            }
        }
        key += 3;
    }

    /* pair at +0x14 */
    rnd = Rand_FloatRange(0.0f, 1.0f);
    vlo = (f32)*(s8 *)(cfg + 0x3E) + (f32)cfg[0x3F] * rnd;
    if (*(u16 *)(cfg + 2) & 0x20) {
        sgn = (f32)(Rand_IntRange(0, 1) * 2 - 1) * D_00384D94;
    } else {
        sgn = D_00384D98;
    }
    k = D_00384D9C;
    key = cfg + 0x40;
    for (i = 0; i < 3; i++) {
        vhi = (f32)*(s8 *)(cfg + 0x41 + 3 * i) + (f32)cfg[0x42 + 3 * i] * rnd;
        if (vlo == 0.0f && vhi == 0.0f) {
            key += 3;
            continue;
        }
        size = *(s16 *)(obj + 4);
        start = FRAME_FLOOR((f32)(size * key[-3]) * k);
        end = FRAME_CEIL((f32)(size * key[0]) * k);
        if (start == end) {
            key += 3;
            continue;
        }
        if (vlo == vhi) {
            func_001C1560(obj, obj + 0x14, start, end, vlo * sgn);
        } else {
            func_001C1650(obj, obj + 0x14, start, end, vlo * sgn, vhi * sgn);
            vlo = vhi;
        }
        key += 3;
    }

    /* vector at +0x20 from arg4 */
    rnd = Rand_FloatRange(0.0f, 1.0f);
    func_00129C28(sp + 0x10, arg4);
    prev = ((f32)cfg[0x4A] + (f32)cfg[0x4B] * rnd) * scale * D_00384DA0;
    *(f32 *)(sp + 0x14) = 0.0f;
    if (prev != 0.0f) {
        Vec3_Scale(sp + 0x20, sp + 0x10, prev);
        *(f32 *)(sp + 0x24) = 0.0f;
        Vec3_Add(obj + 0x20, obj + 0x20, sp + 0x20);
    }
    k = D_00384DA4;
    key = cfg + 0x4C;
    for (i = 0; i < 3; i++) {
        mul = D_00384DA8;
        cur = ((f32)cfg[0x4D + 3 * i] + (f32)cfg[0x4E + 3 * i] * rnd) * scale * mul;
        if (prev != cur) {
            size = *(s16 *)(obj + 4);
            start = FRAME_FLOOR((f32)(size * key[-3]) * k);
            end = FRAME_CEIL((f32)(size * key[0]) * k);
            if (start != end) {
                Vec3_Scale(sp + 0x30, sp + 0x10, (cur - prev) / (f32)(end - start + 1));
                prev = cur;
                *(f32 *)(sp + 0x34) = 0.0f;
                func_001C15A0(obj, obj + 0x20, start, end, sp + 0x30);
            }
        }
        key += 3;
    }

    if (cfg[0x17] != 0) {
        func_001C15F8(obj, obj + 0x1B, 0, cfg[0x17], 0, obj[0x1B]);
    }
    if (cfg[0x18] != 0) {
        size = *(u16 *)(obj + 4);
        func_001C15F8(obj, obj + 0x1B, (s16)(size - cfg[0x18]), (s16)size, obj[0x1B], 0);
    }
    if (*(u16 *)(cfg + 2) & 0x80) {
        f32 r0;
        f32 r1;
        size = *(s16 *)(obj + 4);
        r0 = Rand_FloatRange(0.0f, D_00384DAC) + 1.0f;
        r1 = Rand_FloatRange(D_00384DB0, 0.0f) + 0.0f;
        return func_001C17F8(obj, obj + 0x20, 0, size, (s8)arg5, 1, arg2, r0, r1);
    }
    return 0;
}
