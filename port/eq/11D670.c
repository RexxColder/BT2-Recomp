#include "common.h"

extern void *memset(void *dst, s32 c, u32 n);
extern void *memcpy(void *dst, const void *src, u32 n);
extern f32 fabsf(f32 x);
extern f32 sqrtf(f32 x);
extern u8 D_002C3630[];

void func_002605A0(u8 *arg0, s32 arg1);
s32 BtlStage_FindZoneNear(s32 zone, u8 *center);
f32 sceVu0InnerProduct(u8 *arg0, u8 *arg1);
void func_00312650(f32 *a0, u8 *a1, u8 *a2);
void func_003126C8(void *arg0, void *arg1);
s32 StgCol_SplitStep(u8 *out, u8 *delta, f32 radius, f32 dist);
s32 func_0011D3A0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, u8 *arg4, u8 *arg5, u8 arg6, u8 arg7);

s32 func_0011D670(u8 *arg0, u8 arg1) {
    u8 sp[0x100];
    u8 *s0;
    u8 *s2;
    u8 *s5;
    u8 *s7;
    s32 zone;
    s32 split;
    s32 zone_old;
    s32 v;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 x;
    f32 v13;

    *(u32 *)(arg0 + 0xE50) = *(u32 *)(arg0 + 0xE50) & 0xFFFFFF9F;
    s0 = *(u8 **)(arg0 + 0xF40);
    s2 = *(u8 **)(arg0 + 0xF44);

    if (arg1 != 0) {
        func_002605A0(arg0, 0);
        zone = BtlStage_FindZoneNear(*(s32 *)(arg0 + 0x9F0), s0);
    } else {
        v = *(s32 *)(arg0 + 0x958);
        if (v == 0) {
            f0 = 6.0f;
            f1 = 36.0f;
        } else {
            f1 = *(f32 *)(v + 0x44);
            if (f1 < 0.0f) {
                f0 = *(f32 *)(arg0 + 0xFB8);
                f0 = f0 + f0;
                f1 = f0 * f0;
            } else {
                f0 = f1;
                f1 = f1 * f1;
            }
        }
        *(f32 *)(s0 + 0x10) = f0;
        *(f32 *)(s0 + 0x14) = f1;
        zone = BtlStage_FindZoneNear(*(s32 *)(arg0 + 0x9F0), s0);
    }

    s5 = sp + 0x10;
    s7 = sp + 0x20;
    memset(s7, 0, 0x70);

    if (s2 != 0) {
        memcpy(sp + 0x30, s2, 0x20);
        func_00312650((f32 *)s5, s0, s2);
        x = sceVu0InnerProduct(s5, s5);
        v13 = sqrtf(fabsf(x));
    } else {
        memcpy(sp + 0x30, s0, 0x20);
        func_003126C8(s5, D_002C3630);
        v13 = 0.0f;
    }

    f2 = *(f32 *)(arg0 + 0xFBC);
    if (f2 < 4.0f) {
        *(f32 *)(arg0 + 0xFBC) = 4.0f;
        f2 = 4.0f;
    }
    f0 = *(f32 *)(sp + 0x40);
    if (f0 < f2) {
        *(f32 *)(arg0 + 0xFBC) = f0;
        f2 = f0;
    }

    *(f32 *)(sp + 0x40) = f2;
    *(f32 *)(sp + 0x44) = f2 * f2;
    *(f32 *)(arg0 + 0xFBC) = f2 + 1.0f;
    split = StgCol_SplitStep(sp, s5, f2, v13);

    memcpy(sp + 0x90, sp + 0x20, 0x70);

    if (s2 != 0) {
        zone_old = *(s32 *)(arg0 + 0x9F0);
        if (zone == zone_old) {
            v = func_0011D3A0(arg0, s7, zone, split, sp, s5, 0, arg1);
        } else {
            v = func_0011D3A0(arg0, s7, zone_old, split, sp, s5, 1, arg1);
        }
    } else {
        v = func_0011D3A0(arg0, s7, zone, split, sp, s5, 0, arg1);
    }
    *(s32 *)(arg0 + 0x9F0) = zone;
    return v;
}
