#include "common.h"

extern s32 gEftDust;
extern f32 D_003844B4;
extern f32 D_003844B8;
extern f32 D_003844BC;
extern u8 D_002C3630[];

s32 func_0013E838(void);
void func_003126C8(void *arg0, void *arg1);
f32 EftMath_WrapAngle(f32 farg0);
f32 Mathf_Cos(f32 farg0);
f32 func_0012A3F8(f32 arg0);
void sceVu0Normalize(f32 *arg0, f32 *arg1);

/* 0x0013E898 (EftWaterDrop spawn): allocates a water-drop record, links it into the list whose head is *arg0 and
 * tail is *arg1 (fields 0x68 = previous, 0x6C = next), copies the vectors, and fills the direction vector from two
 * angles (farg0 and farg1 in degrees, scaled by D_003844BC) and farg2. Stack args: farg8 (0x4C scale), farg9 (0x44/0x48
 * period), farg10 (0x58), arg8 (flags, bit 0x100 zeroes 0x44). Bumps gEftDust's counter at 0x2C and returns it
 * (0 when the allocation fails). */
s32 func_0013E898(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                  f32 farg8, f32 farg9, f32 farg10, s32 arg8) {
    u8 *obj;
    u8 *dust;
    f32 angleA;
    f32 angleB;
    f32 yaw;
    f32 cosYaw;
    f32 cosB;
    f32 sinB;
    f32 scale;
    s32 count;

    obj = (u8 *)func_0013E838();
    if (obj == 0) {
        return 0;
    }

    if (*(u8 **)arg0 != 0) {
        *(u8 **)(obj + 0x68) = *(u8 **)arg1;
        *(u8 **)(obj + 0x6C) = 0;
    } else {
        *(u8 **)arg0 = obj;
        *(u8 **)(obj + 0x68) = 0;
        *(u8 **)(obj + 0x6C) = 0;
    }
    if (*(u8 **)arg1 != 0) {
        *(u8 **)(*(u8 **)arg1 + 0x6C) = obj;
    }
    *(u8 **)arg1 = obj;

    func_003126C8(obj, D_002C3630);
    func_003126C8(obj + 0x10, arg2);

    *(f32 *)(obj + 0x3C) = farg3;
    *(f32 *)(obj + 0x40) = farg4;
    *(f32 *)(obj + 0x30) = farg5;
    *(f32 *)(obj + 0x34) = farg6;

    if (farg7 != 0.0f) {
        *(f32 *)(obj + 0x38) = 1.0f / farg7;
    } else {
        *(f32 *)(obj + 0x38) = 0.0f;
    }

    *(f32 *)(obj + 0x4C) = farg8 * D_003844B4;
    *(f32 *)(obj + 0x54) = D_003844B8;
    *(f32 *)(obj + 0x58) = farg10 * 30.0f;
    *(u8 *)(obj + 0x5C) = (u8)arg3;
    *(u8 *)(obj + 0x5D) = (u8)arg4;
    *(u8 *)(obj + 0x5E) = (u8)arg5;
    *(u8 *)(obj + 0x5F) = (u8)arg6;
    *(u8 *)(obj + 0x60) = (u8)arg7;
    *(s32 *)(obj + 0x50) = 0;
    *(s32 *)(obj + 0x64) = arg8;

    angleA = (farg0 / 180.0f) * D_003844BC;
    yaw = EftMath_WrapAngle(angleA);

    *(s32 *)(obj + 0x24) = 0;
    *(f32 *)(obj + 0x20) = func_0012A3F8(yaw);

    angleB = (farg1 / 180.0f) * D_003844BC;

    cosYaw = Mathf_Cos(yaw);
    *(f32 *)(obj + 0x28) = cosYaw;
    *(f32 *)(obj + 0x2C) = 1.0f;

    sceVu0Normalize((f32 *)(obj + 0x20), (f32 *)(obj + 0x20));

    cosB = Mathf_Cos(angleB);
    *(f32 *)(obj + 0x20) = (*(f32 *)(obj + 0x20) * farg2) * cosB;

    sinB = func_0012A3F8(angleB);
    *(f32 *)(obj + 0x24) = (-farg2) * sinB;

    *(f32 *)(obj + 0x28) = (cosYaw * farg2) * cosB;

    scale = farg9 * 30.0f;
    if ((arg8 & 0x100) != 0) {
        *(s32 *)(obj + 0x44) = 0;
    } else {
        *(f32 *)(obj + 0x44) = 128.0f;
    }
    *(f32 *)(obj + 0x48) = 128.0f / scale;

    dust = (u8 *)gEftDust;
    count = *(s32 *)(dust + 0x2C) + 1;
    *(s32 *)(dust + 0x2C) = count;
    return count;
}
