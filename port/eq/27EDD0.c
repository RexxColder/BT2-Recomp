#include "common.h"
void *memset(void *dst, s32 val, u32 n);

void func_003126C8(s32 arg0, s32 arg1);
void Vec3_Hermite(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0);

/* 0x0027EDD0: samples a Hermite curve for i = 0..N, clamps the 4th-row component to 0..255, stores it in arg0's table
 * at index arg0+0xC0 (grown up to 255). Returns the last clamped value. */
f32 func_0027EDD0(void *arg0, void *arg1, void *arg2, void *arg3, s32 arg4) {
    u8 fr[0x60];   /* tamano de locales del original (antes 0x50) */
    u8 *out;
    u8 *obj;
    s32 i;
    s32 p2;
    s32 p3;
    s32 cnt;
    s32 v1;
    f32 t;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f22;
    f32 ret;

    obj = (u8 *)arg0;
    out = (u8 *)arg1;
    memset(fr, 0, 0x50);
    *(f32 *)(fr + 0xC) = 1.0f;
    *(f32 *)(fr + 0x1C) = 1.0f;
    *(f32 *)(fr + 0x2C) = 1.0f;
    *(f32 *)(fr + 0x3C) = 1.0f;
    *(f32 *)(fr + 0x4C) = 1.0f;
    ret = *(f32 *)(fr + 0x48);

    if (arg4 >= 0) {
        f22 = (f32)arg4;
        p2 = (s32)((u8 *)arg2 + 0x10);
        p3 = (s32)((u8 *)arg3 + 0x20);
        i = 0;
        do {
            func_003126C8((s32)fr, (s32)arg2);
            func_003126C8((s32)(fr + 0x10), (s32)arg3);
            func_003126C8((s32)(fr + 0x20), p2);
            t = (f32)i / f22;
            func_003126C8((s32)(fr + 0x30), p3);

            f2 = -*(f32 *)(fr + 0x20);
            f1 = -*(f32 *)(fr + 0x24);
            f0 = -*(f32 *)(fr + 0x28);
            *(f32 *)(fr + 0x20) = f2;
            *(f32 *)(fr + 0x24) = f1;
            *(f32 *)(fr + 0x28) = f0;
            Vec3_Hermite((s32)(fr + 0x40), (s32)fr, (s32)(fr + 0x10), (s32)(fr + 0x20), (s32)(fr + 0x30), t);

            f0 = *(f32 *)(fr + 0x40);
            if (f0 < 0.0f) {
                f0 = 0.0f;
                *(f32 *)(fr + 0x40) = f0;
            }
            f2 = 255.0f;
            if (f2 < f0) {
                *(f32 *)(fr + 0x40) = f2;
            }

            f1 = *(f32 *)(fr + 0x48);
            if (f1 < 0.0f) {
                f1 = 0.0f;
                *(f32 *)(fr + 0x48) = f1;
            }
            if (f2 < f1) {
                f1 = f2;
                *(f32 *)(fr + 0x48) = f2;
            }
            f0 = f1 / f2;

            cnt = *(s32 *)(obj + 0xC0);
            *(f32 *)(out + (cnt << 2)) = f0;
            v1 = *(s32 *)(obj + 0xC0);
            if (v1 < 0xFF) {
                *(s32 *)(obj + 0xC0) = v1 + 1;
            }
            ret = f1;
            i++;
        } while (!(arg4 < i));
    }
    return ret;
}
