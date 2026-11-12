#include "common.h"

f32 EftVolleyAim_Lerp(f32 farg0, f32 farg1, f32 farg2);
f32 sinf(f32 farg0);
void func_00208860(s32 a0, void *a1);
f32 func_00208DC0(s32 arg0);
void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
void Vec3_Add(void *arg0, void *arg1, void *arg2);

/* 0x001C1898: step one keyed value animation. p: +0 kind (0..7), +4/+6 first/last frame (s16), +8 target pointer.
 * Returns 1 when frame is past the last frame, else 0 (frames before the first frame do nothing). */
s32 func_001C1898(u8 *p, s32 frame16) {
    s32 frame = (s16)frame16;
    s32 first = *(s16 *)(p + 4);
    s32 last = *(s16 *)(p + 6);
    f32 *target;
    f32 t;
    f32 f21;
    f32 pos[4];
    f32 diff[4];
    s32 period;
    s32 q;

    if (frame < first) {
        return 0;
    }
    if (last < frame) {
        return 1;
    }
    switch (p[0]) {
    case 0:
        target = *(f32 **)(p + 8);
        target[0] = target[0] + *(f32 *)(p + 0xC);
        break;
    case 1:
        target = *(f32 **)(p + 8);
        target[0] = target[0] + *(f32 *)(p + 0xC);
        target[1] = target[1] + *(f32 *)(p + 0x10);
        target[2] = target[2] + *(f32 *)(p + 0x14);
        break;
    case 2:
        t = (f32)(frame - first) / (f32)(last - first);
        **(u8 **)(p + 8) = (u8)(u32)EftVolleyAim_Lerp((f32)p[0xC], (f32)p[0xD], t);
        break;
    case 3:
        t = (f32)(frame - first) / (f32)(last - first);
        target = *(f32 **)(p + 8);
        target[0] = target[0] + EftVolleyAim_Lerp(*(f32 *)(p + 0xC), *(f32 *)(p + 0x10), t);
        break;
    case 4:
        t = (f32)(frame - first) / (f32)(last - first);
        target = *(f32 **)(p + 8);
        target[0] = target[0] + EftVolleyAim_Lerp(*(f32 *)(p + 0xC), *(f32 *)(p + 0x18), t);
        target = *(f32 **)(p + 8);
        target[1] = target[1] + EftVolleyAim_Lerp(*(f32 *)(p + 0x10), *(f32 *)(p + 0x1C), t);
        target = *(f32 **)(p + 8);
        target[2] = target[2] + EftVolleyAim_Lerp(*(f32 *)(p + 0x14), *(f32 *)(p + 0x20), t);
        break;
    case 5:
        t = (f32)frame / (f32)(last - first);
        f21 = EftVolleyAim_Lerp(*(f32 *)(p + 0xC), *(f32 *)(p + 0x10), t);
        target = *(f32 **)(p + 8);
        target[0] = target[0] + f21 * sinf(EftVolleyAim_Lerp(*(f32 *)(p + 0x14), *(f32 *)(p + 0x18), t));
        break;
    case 6:
        period = *(s16 *)(p + 0xC);
        if (frame % period != 0) {
            return 0;
        }
        q = frame / period;
        **(u8 **)(p + 8) = **(u8 **)(p + 8) + (*(u8 **)(p + 0x10))[q % *(s32 *)(p + 0x14)];
        break;
    case 7:
        t = (f32)frame / (f32)(last - first);
        f21 = EftVolleyAim_Lerp(*(f32 *)(p + 0x10), *(f32 *)(p + 0x14), t);
        if (f21 == 0.0f) {
            return 0;
        }
        func_00208860((s8)p[0xC], pos);
        if (p[0xD] != 0) {
            pos[1] = func_00208DC0((s8)p[0xC]);
        }
        diff[0] = pos[0] - *(f32 *)(p + 0x18);
        diff[1] = pos[1] - *(f32 *)(p + 0x1C);
        diff[2] = pos[2] - *(f32 *)(p + 0x20);
        Vec3_Scale((u8 *)diff, (u8 *)diff, f21);
        target = *(f32 **)(p + 8);
        Vec3_Add(target, target, diff);
        *(f32 *)(p + 0x18) = pos[0];
        *(f32 *)(p + 0x20) = pos[2];
        *(f32 *)(p + 0x1C) = pos[1];
        break;
    default:
        break;
    }
    return 0;
}
