#include "common.h"

extern f32 D_003868E0;
extern f32 D_003868E4;
extern f32 D_003868E8;
extern f32 D_003868EC;
extern f32 D_003868F0;

s32 func_00212320(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_001FA2E0(s32 arg0);
void func_00230BB0(s32 arg0, s32 arg1);
void func_00230C48(s32 arg0);
void func_00230C60(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001FA110(s32 arg0, s32 arg1);
void BtlChar_SetVibration(s32 arg0, f32 farg0, f32 farg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_001F9D78(s32 arg0, s32 arg1);
s32 func_00241778(s32 arg0, s32 arg1);
s32 func_00203310(s32 arg0, s32 arg1, s32 arg2);
void func_001FCD80(s32 arg0);
s32 func_00230D30(s32 arg0, s32 arg1, s32 arg2);
void func_002310B8(s32 arg0, s32 arg1, s32 arg2);
void func_001F9FB0(s32 arg0, s32 arg1);
s32 func_002411E0(s32 arg0, s32 arg1);
void func_002177A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
void func_00206958(s32 arg0, s64 arg1);

/* Per-frame update of a character's finishing-move phase (arg0 = character): the animation id from
   BtlObjXf_Update picks one of 8 sub-actions (switch over the three costume variants 284..290,
   318..324, 352..358 and 386), each stepping the counter at +0x8C0 or requesting the next animation;
   then common effect / flag setup. */
void func_002329E0(s32 arg0) {
    s32 *counter = (s32 *)(arg0 + 0x8C0);
    s32 hit = 0;
    s32 runFx = 1;
    s32 owner;
    s32 anim;

    owner = func_00212320(arg0);
    switch (BtlObjXf_Update(arg0)) {
    case 284:
    case 318:
    case 352:
        func_001FA0A0(arg0, BtlObjXf_Update(arg0) + 1, 0);
        if (func_001FA2E0(arg0) != 0) {
            func_00230BB0(arg0, owner);
        }
        func_00230C60(arg0, 0);
        hit = 1;
        func_002113C0(arg0, 9, 4, 1);
        break;
    case 285:
    case 319:
    case 353:
        func_001FA110(arg0, 0);
        BtlChar_SetVibration(arg0, D_003868E0, D_003868E4);
        *counter = *counter + 1;
        if (*counter >= 0x97) {
            func_002113C0(arg0, 7, 1, 1);
        }
        if (func_00211310(arg0, 7, 1) != 0) {
            func_001F9D78(arg0, BtlObjXf_Update(arg0) + 1);
            *counter = 0;
        }
        func_00230C60(arg0, 0);
        hit = 1;
        func_002113C0(arg0, 9, 4, 1);
        break;
    case 286:
    case 320:
    case 354:
        if (func_001FA0A0(arg0, BtlObjXf_Update(arg0) + 1, 0) != 0) {
            anim = func_00241778(arg0, owner);
            if (func_00203310(arg0, anim, 0x2F) != 0) {
                func_002113C0(arg0, 6, 4, 1);
            }
        }
        if (func_001FA2E0(arg0) != 0) {
            func_001FCD80(arg0);
        }
        func_00230C60(arg0, 1);
        func_00230D30(arg0, owner, 0);
        func_002310B8(arg0, owner, 0);
        break;
    case 287:
    case 321:
    case 355:
        func_001FA110(arg0, 0);
        func_00230D30(arg0, owner, 1);
        func_002310B8(arg0, owner, 1);
        func_00230C60(arg0, 1);
        *counter = *counter + 1;
        if (*counter >= 0x97) {
            func_002113C0(arg0, 7, 2, 1);
        }
        if (func_00211310(arg0, 7, 2) != 0) {
            func_001F9D78(arg0, BtlObjXf_Update(arg0) + 1);
            *counter = 0;
        }
        break;
    case 288:
    case 322:
    case 356:
        func_001FA0A0(arg0, BtlObjXf_Update(arg0) + 1, 0);
        break;
    case 289:
    case 323:
    case 357:
        func_001FA110(arg0, 0);
        *counter = *counter + 1;
        if (*counter >= 0x97) {
            func_002113C0(arg0, 7, 8, 1);
        }
        if (func_00211310(arg0, 7, 8) != 0) {
            func_001F9D78(arg0, BtlObjXf_Update(arg0) + 1);
            *counter = 0;
        }
        break;
    case 290:
    case 324:
    case 358:
        func_001F9FB0(arg0, 0);
        break;
    case 386:
        func_001FA0A0(arg0, 0x160, 0);
        if (func_001FA2E0(arg0) != 0) {
            func_00230C48(arg0);
        }
        func_00230C60(arg0, 0);
        runFx = 0;
        func_002113C0(arg0, 9, 4, 1);
        break;
    default:
        break;
    }

    if (runFx != 0 && (func_002411E0(arg0, owner) & 0x400000) == 0) {
        s32 from = BtlObjXf_Update(arg0) + 7;
        s32 to = BtlObjXf_Update(arg0) + 0xE;

        func_002177A8(arg0, from, to, hit);
    }
    func_00215068(arg0, 5, 0xC, D_003868EC, D_003868E8);
    func_00215E88(D_003868E8, arg0, 6);
    func_00216208(arg0, 0.0f, D_003868F0);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xD, 1, 1);
    func_002113C0(arg0, 0xD, 0x10, 1);
    func_002113C0(arg0, 9, 0x40000, 1);
    func_002113C0(arg0, 1, 0x800000, 1);
    if ((func_002411E0(arg0, owner) & 0x10) == 0) {
        func_00206958(arg0, 0x8000);
    }
    if (func_00211310(arg0, 0, 2) != 0) {
        return;
    }
    if (func_00211310(arg0, 0, 4) != 0) {
        return;
    }
    func_002113C0(arg0, 0, 2, 1);
}
