#include "common.h"

extern u8 D_002C3630[];
extern f32 D_00386AF8;
extern f32 D_00386AFC;
extern f32 D_00386B00;
extern f32 D_00386B04;
extern f32 D_00386B08;
extern f32 D_00386B0C;

void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0020FC38(u8 *arg0, s32 arg1);
void func_00212DD8(u8 *arg0, s32 arg1);
s32 func_00217488(u8 *arg0);
void func_00206958(u8 *arg0, s32 arg1);
s32 BtlObjXf_Update(u8 *arg0);
s32 func_001F9FB0(u8 *arg0, s32 arg1);
void func_001F9F90(u8 *arg0);
void func_001FA110(u8 *arg0, s32 arg1);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
void func_001F9D78(u8 *arg0, s32 arg1);
s32 func_002125D8(u8 *arg0);
s32 func_0023F478(u8 *arg0, s32 arg1);
void BtlMember_SubBlast(u8 *arg0, s32 arg1);
void BtlMove_BrakeVertical(u8 *arg0);
s32 func_001FA2E0(u8 *arg0);
s32 func_0023F410(u8 *arg0);
u8 *BtlChar_GetPos(u8 *arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 func_001FC3B0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);
s32 func_001FBE80(u8 *arg0, f32 farg0, f32 farg1);
void BtlChar_Vibrate(u8 *a0, f32 f12, f32 f13);
void func_00212890(s32 arg0);
void func_00216678(u8 *arg0);
void func_00210618(u8 *arg0, s32 arg1);
void func_00215068(u8 *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(u8 *arg0, s32 arg1, f32 farg0);
void func_00216208(u8 *arg0, f32 farg0, f32 farg1);

/* 0x00238908: end-of-action state handler for a battle member: switches on the current motion id from
   BtlObjXf_Update (398/430 -> idle, 399/431 -> hit-recover, 400 -> blast fly, 432 -> fall), then sets a fixed set of flags. */
s32 func_00238908(u8 *obj) {
    s32 motion;
    s32 v;
    s32 blast;
    f32 yaw;
    f32 side;
    f32 height;
    f32 height2;
    f32 f20;

    if (*(s32 *)(obj + 0x8CC) == 1) {
        func_002113C0(obj, 12, 1, 1);
        func_0020FC38(obj, 0x54);
        func_00212DD8(obj, 14);
        if (func_00217488(obj) != 49) {
            func_00206958(obj, 1);
        }
    }
    motion = BtlObjXf_Update(obj);
    switch (motion) {
    case 398:
    case 430:
        if (func_001F9FB0(obj, 0) != 0) {
            func_001F9F90(obj);
        }
        BtlMove_BrakeVertical(obj);
        break;
    case 399:
    case 431:
        func_001FA110(obj, 0);
        if (func_00211310(obj, 12, 4) != 0) {
            v = func_00217488(obj);
            if (v >= 46) {
                if (v >= 49) {
                    if (v == 49) {
                        func_001F9D78(obj, 432);
                    }
                } else {
                    func_001F9D78(obj, 400);
                }
            }
            blast = func_002125D8(obj);
            blast = func_0023F478(obj, blast);
            BtlMember_SubBlast(obj, blast);
            func_002113C0(obj, 12, 8, 1);
        }
        BtlMove_BrakeVertical(obj);
        break;
    case 400:
        if (func_001FA2E0(obj) != 0) {
            func_00206958(obj, 2);
            func_002113C0(obj, 12, 0x10, 1);
            if ((func_0023F410(obj) & 0x40000) != 0) {
                func_0020FC38(obj, 0x4C);
            } else {
                func_0020FC38(obj, 0x53);
            }
            func_00212DD8(obj, 0x22);
            side = D_00386AFC;
            yaw = BtlUtil_WrapAngle(*(f32 *)(BtlChar_GetPos(obj) + 0xB4) + D_00386AF8);
            height = BtlCharApi_GetHeight(*(s32 *)(obj + 0x1534)) * D_00386B00;
            height2 = BtlCharApi_GetHeight(*(s32 *)(obj + 0x1534));
            func_001FC3B0(obj, (s32)D_002C3630, (s32)D_002C3630, (s32)D_002C3630, (s32)D_002C3630,
                          (s32)D_002C3630, (s32)D_002C3630, 17, 17, 17, 17, 8, 197,
                          yaw, 0.0f, 0.0f, 0.0f, height, (0.0f - height2) * side);
            func_001FBE80(obj, 5.0f, side);
            BtlChar_Vibrate(obj, 1.0f, 0.5f);
        } else {
            func_002113C0(obj, 12, 0x10, 0);
        }
        if (func_001F9FB0(obj, 0) != 0) {
            func_00206958(obj, 4);
            func_00212890(60);
        }
        func_00216678(obj);
        func_002113C0(obj, 1, 0x2000, 1);
        break;
    case 432:
        if (func_001FA2E0(obj) != 0) {
            func_002113C0(obj, 12, 0x10, 1);
            func_00210618(obj, 0x3C1F);
        } else {
            func_002113C0(obj, 12, 0x10, 0);
        }
        func_001F9FB0(obj, 0);
        func_00216678(obj);
        break;
    default:
        break;
    }
    f20 = D_00386B04;
    func_00215068(obj, 5, 12, D_00386B08, f20);
    func_00215E88(obj, 7, f20);
    func_00216208(obj, 0.0f, D_00386B0C);
    func_002113C0(obj, 9, 0x10000, 1);
    func_002113C0(obj, 9, 4, 1);
    func_002113C0(obj, 3, 0xF, 1);
    func_002113C0(obj, 13, 8, 1);
    func_002113C0(obj, 13, 0x10, 1);
    func_002113C0(obj, 13, 1, 1);
    func_002113C0(obj, 3, 0x800, 1);
    func_002113C0(obj, 9, 0x200000, 1);
    func_002113C0(obj, 1, 0x800, 1);
    func_002113C0(obj, 15, 0x100000, 1);
    obj[0x1014] = 1;
    return 1;
}
