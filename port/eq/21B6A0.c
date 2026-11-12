#include "common.h"

f32 func_00240D50(s32 arg0, s32 arg1);
s32 func_00240EA8(s32 arg0, s32 arg1);
s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA0A0(s32 a0, s32 a1, s32 a2);
void BtlChar_SetVibration(s32 arg0, f32 farg0, f32 farg1);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_001F9D78(s32 arg0, s32 arg1);
f32 func_001FA318(s32 arg0);
void func_00206958(s32 arg0, s64 arg1);
s32 func_00203888(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_001F9FB0(s32 arg0, s32 arg1);
void func_001FA380(s32 arg0, f32 arg1);
void *BtlChar_GetPos(s32 arg0);
s32 func_00217BD0(s32 arg0);
f32 func_001FA308(s32 arg0);
s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215550(void *a0, s32 a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18);
void func_00215068(void *a0, s32 a1, s32 a2, f32 fMax, f32 fScale);
void func_00215E88(s32 a0, u32 a1);
void func_00216208(f32 farg0, f32 farg1, s32 arg0);
void func_00216678(s32 a0);
extern f32 D_00385CA4;
extern f32 D_00385CA8;
extern f32 D_00385CAC;
extern f32 D_00385CB0;
extern f32 D_00385CB4;
extern f32 D_00385CB8;
extern f32 D_00385CBC;
extern f32 D_00385CC0;
extern f32 D_00385CC4;

/* 0x0021B6A0: character action update, dispatched on the animation id (0x68..0x76). */
void func_0021B6A0(s32 obj) {
    u8 *self = (u8 *)(u32)obj;
    s32 grounded = 1;
    s32 mode2;
    s32 anim;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 rate;

    f21 = func_00240D50(obj, 6);
    mode2 = func_00240EA8(obj, 0) * 2;
    anim = BtlObjXf_Update(obj);
    f22 = f21;
    f23 = D_00385CA4;
    switch (anim - 0x68) {
    case 0:
    case 3:
    case 6:
    case 9:
    case 12:
        func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0);
        goto common;
    case 1:
    case 4:
    case 7:
    case 10:
    case 13:
        if (func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0) != 0) {
            BtlChar_SetVibration(obj, 1.0f, D_00385CA8);
        } else if (BtlPad_Test48(obj, 0) == 0 || func_00211310(obj, 0, 1) == 0) {
            func_001F9D78(obj, BtlObjXf_Update(obj) + 1);
        }
        *(f32 *)(self + 0x9B0) = func_001FA318(obj);
        func_00206958(obj, 0x40000);
    common:
        func_00206958(obj, 8);
        func_00206958(obj, 0x400);
        BtlChar_SetVibration(obj, D_00385CAC, D_00385CB0);
        func_00203888(obj, mode2, 0);
        func_002113C0(obj, 7, 0x80000, 1);
        break;
    case 2:
    case 5:
    case 8:
    case 11:
    case 14:
        func_001F9FB0(obj, 0);
        func_001FA380(obj, 2.0f);
        if (func_00211310(obj, 4, 2) != 0) {
            f21 = 0.0f;
            *(f32 *)((u8 *)BtlChar_GetPos(obj) + 0xC0) = f21;
        }
        if (func_00211310(obj, 4, 0xC) != 0) {
            f21 = 0.0f;
            f23 = D_00385CB4;
            grounded = 0;
            if (func_00217BD0(obj) != 0) {
                *(f32 *)((u8 *)BtlChar_GetPos(obj) + 0xC0) = f21;
            }
        }
        f20 = func_001FA308(obj) - 15.0f;
        if (f20 < (f32)BtlObjAnim_QueryEvent(*(s32 *)(self + 0x1530), 2, 0, 1)) {
            func_00206958(obj, 0x40000);
        }
        break;
    default:
        break;
    }
    if (func_00211310(obj, 0, 1) != 0 && grounded != 0) {
        rate = 1.0f - (f32)*(s32 *)(self + 0x8CC) * 3.0f / 30.0f;
        if (rate < 0.0f) {
            rate = 0.0f;
        }
        func_00215550(self, 1, f22, D_00385CC0, D_00385CC0, rate * D_00385CBC, rate * D_00385CB8,
                      D_00385CB8, 1.0f);
    } else {
        func_00215068(self, 5, 13, D_00385CC4, 1.0f);
    }
    func_00215E88(obj, 3);
    func_00216208(f21, f23, obj);
    func_00216678(obj);
    func_002113C0(obj, 5, 0x40, 1);
    func_002113C0(obj, 1, 0x2000, 1);
    func_002113C0(obj, 15, 0x40, 1);
    func_002113C0(obj, 9, 0x200, 1);
    func_002113C0(obj, 13, 8, 1);
    func_00206958(obj, 0x80000000000LL);
    func_002113C0(obj, 1, 0x800000, 1);
}
