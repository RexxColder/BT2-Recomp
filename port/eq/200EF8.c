#include "common.h"

extern s32 BtlObjXf_Update(s32 arg0);
extern s32 func_001FA3A8(s32 arg0);
extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern f32 func_00200550(s32 arg0, s32 arg1, f32 *arg2);
extern u8 *BtlChar_GetPos(s32 arg0);
extern f32 BtlUtil_WrapAngle(f32 farg0);
extern s32 func_002407A0(s32 arg0);
extern s32 BtlKiBlast_GetReactS4000Of_240848(s32 arg0, u32 kind);
extern s32 BtlKiBlast_GetReactS200Of_2408F0(s32 arg0, u32 kind);
extern s32 func_0023F410(s32 arg0);
extern s32 func_00218128(s32 arg0, s32 arg1);
extern s32 func_00240040(s32 arg0);
extern s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_00240728(s32 arg0);
extern f32 func_00240B98(s32 arg0);
extern void Vec3_DiffToEuler_20E478(f32 farg0, s32 arg0, f32 *arg1);
extern void func_00212DD8(s32 arg0, s32 arg1);
extern void func_00206958(s32 arg0, s64 arg1);
extern s32 BtlKiBlast_GetHitsOf_240980(s32 arg0);
extern void func_00210000(s32 arg0, s32 arg1);
extern s32 BtlChar_FrameMod(s32 arg0);
extern s32 func_00240148(s32 arg0);
extern void func_00203310(s32 arg0, s32 arg1, s32 arg2);
extern void func_001FBE80(s32 arg0, f32 farg0, f32 farg1);
extern void BtlChar_Vibrate(s32 arg0, f32 farg0, f32 farg1);
extern void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_003858B8;
extern f32 D_003858BC;

/* Starts the hit reaction of a member struck by a ki blast: picks the reaction id from the hit
   flags (0x100000 / 0x800000 / 0x40000 / guard / 0x20000), fills the reaction record at +0xB48,
   plays the impact effect and bumps the hit counter (+0x1470). Returns 1 when a reaction ran. */
s32 func_00200EF8(s32 obj, s32 hit) {
    u8 *self = (u8 *)obj;
    f32 dir[4];
    s32 hitFlags;
    f32 aim;
    s32 facing;
    s32 react;
    s32 s1;
    s32 sub;
    f32 f20;

    if (*(s32 *)((u8 *)hit + 0x68) == 0) {
        return 0;
    }
    hitFlags = func_001FA3A8(BtlObjXf_Update(obj));
    if (func_00211310(obj, 3, 2)) {
        return 0;
    }
    if (hitFlags & 0x40) {
        return 1;
    }
    aim = func_00200550(obj, hit, dir);
    facing = 1;
    if (!(__builtin_fabsf(BtlUtil_WrapAngle(*(f32 *)(BtlChar_GetPos(obj) + 0x14) - aim)) < D_003858B8)) {
        facing = 0;
    }
    react = 2;
    if (*(s32 *)(self + 0xADC) <= 0) {
        if (hitFlags & 0x100000) {
            react = func_002407A0(hit);
        } else if (hitFlags & 0x800000) {
            react = BtlKiBlast_GetReactS4000Of_240848(hit, 2); /* asm: a1 = 2 */
        } else if (hitFlags & 0x40000) {
            react = BtlKiBlast_GetReactS200Of_2408F0(hit, 2);
        } else {
            s1 = (func_0023F410(obj) & 4) != 0;
            if (func_00218128(obj, 6)) {
                s1 = 1;
            }
            if (*(s32 *)(self + 0xAD8) > 0) {
                s1 = 1;
            }
            if (s1 > 0 && (func_00240040(hit) & 0x10)) {
                react = 2;
            } else if ((hitFlags & 0x20000) && (func_00240040(hit) & 0x10)) {
                u8 *anim = *(u8 **)(self + 0x1530);

                react = 2;
                if (BtlObjAnim_QueryEvent((s32)anim, 1, 0, 2) != 0 &&
                    (s8)anim[0xD7D] == ~(s32)(s8)anim[0xD7C]) {
                    react = func_00240728(hit);
                }
            } else {
                react = func_00240728(hit);
            }
        }
    }

    if (react == 2) {
        *(s32 *)(self + 0xB48 + 0x34) = 3;
        *(s32 *)(self + 0xB48) = react;
    } else {
        *(s32 *)(self + 0xB48) = react;
        *(s32 *)(self + 0xB48 + 0x10) = 0;
        *(s32 *)(self + 0xB48 + 0x18) = 0;
        *(s32 *)(self + 0xB64) = 0;
        *(s32 *)(self + 0xB68) = 0;
        self[0xB48 + 0xC] = facing;
        *(f32 *)(self + 0xB48 + 0x14) = aim;
        Vec3_DiffToEuler_20E478(func_00240B98(hit), obj, dir);
        func_00212DD8(obj, 0);
    }
    func_00206958(obj, 0x800000);
    if (BtlKiBlast_GetHitsOf_240980(hit) == 14) {
        func_00210000(hit + 0x20, 0x42);
    } else {
        func_00210000(hit + 0x20, BtlChar_FrameMod(2) ? 0x1B : 0x11);
    }
    f20 = D_003858BC;
    func_00203310(obj, func_00240148(hit), 0);
    func_001FBE80(obj, 3.0f, f20);
    BtlChar_Vibrate(obj, 1.0f, f20);
    sub = *(s16 *)(*(u8 **)((u8 *)hit + 0x68) + 0x18);
    switch (sub) {
    case 1: case 2: case 3: case 5: case 6: case 7: case 9: case 10: case 11:
        func_002113C0(obj, 16, 0x10000, 1);
        break;
    default:
        break;
    }
    *(s32 *)(self + 0x1470) = *(s32 *)(self + 0x1470) + 1;
    return 1;
}
