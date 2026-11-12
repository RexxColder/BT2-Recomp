#include "common.h"

extern f32 D_0038478C;
extern f32 D_00384790;
extern f32 D_00384794;
extern f32 D_00384798;

s32 BtlCharApi_IsHidden(void *arg0);
void func_00208DE8(void *arg0, void *arg1, s32 arg2);
void Vec3_Normalize(f32 *arg0, f32 *arg1);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void Vec3_Add(f32 *arg0, f32 *arg1, f32 *arg2);
void func_00163710(void *arg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6);
void func_0019F370(void *arg0, s32 arg1);
void func_001F45C0(f32 farg0);
void func_001F45D8(void *arg0);
void func_00163AD8(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 t0, f32 farg0);
void func_00162F98(void *arg0, void *arg1, void *arg2);

void func_00163EA0(u8 *arg0) {
    u8 *s1;
    u8 *s0;
    u8 *s2;
    u8 *s3;
    f32 sp0[4];
    f32 sp10[4];
    f32 sp20[4];
    s32 hidden;
    s32 ab4;
    s32 a2;
    f32 f0;
    f32 f1;

    s1 = *(u8 **)(arg0 + 0x38);
    s3 = s1 + 0x50;
    s2 = *(u8 **)(s1 + 0xB0);
    s0 = s1 + 0xA0;
    *(s32 *)(s1 + 0xAB4) = *(s32 *)(s1 + 0xAB4) + 1;
    a2 = *(s32 *)(s1 + 0x8);
    func_00208DE8(*(void **)s2, s3, a2);
    Vec3_Normalize((f32 *)s0, (f32 *)s0);
    func_00129BD0(s0, s0, 60.0f);
    Vec3_Add((f32 *)(s1 + 0x80), (f32 *)s3, (f32 *)s0);

    hidden = BtlCharApi_IsHidden(*(void **)s2);
    ab4 = *(s32 *)(s1 + 0xAB4);
    if (hidden != 0 || ab4 >= 0x49B) {
        f0 = *(f32 *)(s1 + 0x54);
        f1 = *(f32 *)(s1 + 0x84);
        f0 = f0 + 200.0f;
        f1 = f1 + 200.0f;
        *(f32 *)(s1 + 0x54) = f0;
        *(f32 *)(s1 + 0x84) = f1;
    }

    /* the 3-frame block: AB4 divisible by 3 */
    if (ab4 % 3 == 0) {
        func_00208DE8(*(void **)s2, sp0, 3);
        func_00163710(sp0, D_0038478C, 5.0f, 45.0f, D_00384790, 4.0f, D_00384794);
        func_00163710(sp0, D_0038478C, 5.0f, 15.0f, D_00384790, 4.0f, D_00384794);
    }

    ab4 = *(s32 *)(s1 + 0xAB4);
    if (ab4 == 0x355) {
        func_00208DE8(*(void **)s2, sp10, 0x30);
        func_0019F370(sp10, 0);
    }

    ab4 = *(s32 *)(s1 + 0xAB4);
    if ((u32)(ab4 - 0x47D) < 0x97U) {
        *(f32 *)(s1 + 0xAB0) = 1.0f;
        func_001F45C0(1.0f);
        func_001F45D8(s1 + 0x30);
        *(s32 *)s1 = *(s32 *)s1 | 0x800;
    }

    ab4 = *(s32 *)(s1 + 0xAB4);
    if (ab4 == 0x4A0) {
        sp20[0] = 256.0f;
        sp20[1] = 224.0f;
        *(s32 *)&sp20[2] = 0;
        sp20[3] = 1.0f;
        func_00163AD8(*(void **)s2, sp20, 0, 0, 1, D_00384798);
    }

    ab4 = *(s32 *)(s1 + 0xAB4);
    if (ab4 == 0x514) {
        *(s32 *)(s1 + 0xAB0) = 0;
        func_001F45C0(0.0f);
        func_001F45D8(s1 + 0x30);
        *(s32 *)s1 = *(s32 *)s1 | 0x400;
    }

    func_00162F98(*(void **)s2, s1 + 0x860, s3);
}
