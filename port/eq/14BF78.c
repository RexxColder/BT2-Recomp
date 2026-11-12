#include "common.h"

s32 Rand_IntRange(s32 lo, s32 hi);
f32 Rand_FloatRange(f32 lo, f32 hi);
f32 EftVolleyAim_Lerp(f32 farg0, f32 farg1, f32 farg2);
s32 Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void EftVolleyAim_GetToOpponent(s32 arg0, s32 arg1);
f32 func_00129E30(u8 *arg0);
void func_001EEDB8(f32 *arg0, f32 *arg1, f32 farg0);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
void Vec4_Scale(u8 *arg0, u8 *arg1, f32 farg0);
void Vec4_Add(u8 *arg0, u8 *arg1, u8 *arg2);
f32 sqrtf(f32 farg0);
void func_00181F58(u8 *self, s32 arg1, u8 *arg2, u8 flag);
extern f32 D_003845B0;
extern f32 D_003845B4;
extern f32 D_003845B8;
extern f32 D_003845BC;

#define ADDR(p) ((s32)(u32)(p))

/* 0x0014BF78: run the camera/aim script of a shot for one frame (frame = a2) and then apply it.
 * The script is a list of 8-byte entries at shot+0xB1C: type (s32), first frame, last frame, two parameter bytes;
 * ends with type 0. Entries outside [first, last] are skipped. */
void func_0014BF78(u8 *self, u8 *out, s32 frame) {
    u8 *shot = *(u8 **)(*(u8 **)(self + 0x20) + 0x38);
    u8 *entry = *(u8 **)(shot + 0xB1C);
    s32 *shooter = *(s32 **)(shot + 0xB0);
    u8 *aim;
    u8 *e;
    s32 first;
    s32 last;
    f32 t;
    f32 f12;
    f32 f13;
    f32 len2;
    f32 len;
    f32 f21;
    f32 dir[4];
    s32 r;

    if (entry != NULL) {
        while (*(s32 *)entry != 0) {
            e = entry;
            first = e[4];
            last = e[5];
            if (frame < first || last < frame) {
                entry += 8;
                continue;
            }
            switch (*(s32 *)e - 1) {
            case 0:
                f12 = *(f32 *)(out + 0x48) * (f32)e[6] * D_003845B0;
                f13 = *(f32 *)(out + 0x48) * (f32)e[7] * D_003845B0;
                t = 1.0f;
                if (frame != first) {
                    t = (f32)(frame - first) / (f32)(last - first);
                }
                *(f32 *)(out + 0x4C) = EftVolleyAim_Lerp(f12, f13, t);
                break;
            case 1:
                f12 = *(f32 *)(out + 0x40) * (f32)e[6] * D_003845B4;
                f13 = *(f32 *)(out + 0x40) * (f32)e[7] * D_003845B4;
                t = 1.0f;
                if (frame != first) {
                    t = (f32)(frame - first) / (f32)(last - first);
                }
                *(f32 *)(out + 0x44) = EftVolleyAim_Lerp(f12, f13, t);
                break;
            case 2:
                aim = shot + (self[1] << 4) + 0xB20;
                r = Rand_IntRange(0, e[7]);
                if (r == 0 || (self[0] & 4) != 0) {
                    Vec4_Set(ADDR(aim), 0.0f, 0.0f, 0.0f, 1.0f);
                    f21 = (f32)e[6] * D_003845B8;
                } else if (Rand_IntRange(0, e[7] >> 1) == 0) {
                    Vec4_Set(ADDR(aim), 0.0f, 0.0f, 0.0f, 1.0f);
                    f21 = (f32)e[6] * D_003845BC;
                } else {
                    EftVolleyAim_GetToOpponent(*shooter, ADDR(aim));
                    len2 = func_00129E30(aim);
                    if (len2 < (f32)(e[6] * e[6])) {
                        len = sqrtf(len2);
                    } else {
                        len = (f32)e[6];
                    }
                    func_001EEDB8((f32 *)aim, (f32 *)aim, len * -0.5f);
                    f21 = (f32)e[6];
                }
                *(f32 *)aim = *(f32 *)aim + Rand_FloatRange(-f21, f21);
                *(s32 *)(aim + 4) = 0;
                *(f32 *)(aim + 8) = *(f32 *)(aim + 8) + Rand_FloatRange(-f21, f21);
                break;
            case 3:
                aim = shot + (self[1] << 4) + 0xB20;
                EftVolleyAim_GetToOpponent(*shooter, ADDR(aim));
                *(s32 *)(aim + 4) = 0;
                func_001EEDB8((f32 *)aim, (f32 *)aim, -1000.0f);
                break;
            case 4:
                aim = shot + (self[1] << 4) + 0xB20;
                EftVolleyAim_GetToOpponent(*shooter, ADDR(aim));
                *(s32 *)(aim + 4) = 0;
                func_001EEDB8((f32 *)aim, (f32 *)aim, -1000.0f);
                Vec3_Normalize((u8 *)dir, out + 0x10);
                *(s32 *)&dir[1] = 0;
                Vec4_Scale((u8 *)dir, (u8 *)dir, -400.0f);
                Vec4_Add(aim, aim, (u8 *)dir);
                *(f32 *)(aim + 4) = *(f32 *)(aim + 4) - 1000.0f;
                break;
            case 5:
                shot[self[1] + 0xCA0] = e[6];
                break;
            default:
                break;
            }
            entry += 8;
        }
    }
    func_00181F58(out, *shooter, shot + (self[1] << 4) + 0xB20, shot[self[1] + 0xCA0]);
}
