#include "common.h"

extern f32 D_003860F8;
extern f32 D_003860FC;
extern f32 D_00386100;
extern f32 D_00386104;
extern f32 D_00386108;
extern f32 D_0038610C;
extern f32 D_00386110;
extern f32 D_00386114;

s32 BtlObjXf_Update(void *arg0);
void *BtlChar_GetPos(void *arg0);
void BtlChar_SetVibration(void *arg0, f32 farg0, f32 farg1);
void BtlChar_Vibrate(void *arg0, f32 farg0, f32 farg1);
void BtlMember_AddMaxPower(void *arg0, s32 arg1);
s32 BtlMember_HasBlast(void *arg0, s32 arg1);
s32 BtlMember_IsKiFull(void *arg0);
s32 BtlMember_IsMaxPowerFull(void *arg0);
void BtlMember_SubBlast(void *arg0, s32 arg1);
s32 func_001FA0A0(void *arg0, s32 arg1, s32 arg2);
void func_001FA110(void *arg0, s32 arg1);
s32 func_001FA1D0(void *arg0, f32 farg0);
void func_001FBE80(void *arg0, f32 farg0, f32 farg1);
void func_001F9D78(void *arg0, s32 arg1);
void func_001F9FB0(void *arg0, s32 arg1);
void func_00203810(void *arg0, s32 arg1);
void func_00206958(void *arg0, s64 arg1);
void func_0020FC38(void *arg0, s32 arg1);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00211418(void *arg0, s32 arg1);
void func_00212DD8(void *arg0, s32 arg1);
void func_00215068(void *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, void *arg0, s32 arg1);
void func_00216208(void *arg0, f32 farg0, f32 farg1);
void func_00216678(void *arg0);
s32 func_0023F410(void *arg0);
s32 func_0023F430(void *arg0);
s32 func_0023F9C0(void *arg0);
s32 func_0023FA18(void *arg0);
s32 func_0023FBD8(void *arg0);
void func_0026A2B0(s32 arg0, void *arg1, f32 farg0);
void func_00312680(f32 farg0, void *arg0, void *arg1);
f32 sinf(f32 x);
f32 cosf(f32 x);

void func_00223AA8(void *arg0) {
    f32 sp[4];
    s32 r;
    s32 s1;
    f32 f20;
    f32 sn;
    f32 cs;

    r = BtlObjXf_Update(arg0);
    switch (r) {
    case 0x40:
        if (func_001FA0A0(arg0, 0x41, 1) != 0) {
            if (func_0023F430(arg0) & 0x100) {
                func_0020FC38(arg0, 0x3E);
            } else {
                func_0020FC38(arg0, 0x15);
            }
            func_00212DD8(arg0, 0xD);
            func_00211418(arg0, 0x100);
        }
        break;
    case 0x41:
        func_001FA110(arg0, 0);
        if (func_0023F430(arg0) & 0x100) {
            func_0020FC38(arg0, 0x3F);
        } else {
            func_0020FC38(arg0, 0x16);
        }
        func_00206958(arg0, 0x40);
        if (func_00211310(arg0, 0, 0x100) != 0) {
            s1 = func_0023FA18(arg0);
        } else {
            s1 = func_0023F9C0(arg0);
        }
        if (func_00211310(arg0, 0, 0x1000) != 0) {
            s1 = s1 / 2;
        }
        f20 = D_003860F8;
        func_00203810(arg0, s1);
        BtlChar_SetVibration(arg0, D_003860FC, f20);
        if (func_0023F430(arg0) != 0x80) {
            sn = sinf(*(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0x14));
            sp[1] = -1.0f;
            sp[0] = -sn;
            cs = cosf(*(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0x14));
            sp[2] = -cs;
            func_00312680(f20, sp, sp);
            func_0026A2B0(*(s32 *)((u8 *)arg0 + 0x1530), sp, 3.0f);
        }
        if (func_00211310(arg0, 0, 4) != 0) {
            func_00206958(arg0, (s32)((s64)0x8000 << 24));
        }
        if (BtlMember_IsKiFull(arg0) != 0) {
            if (BtlMember_HasBlast(arg0, 0x186A0) != 0) {
                BtlMember_AddMaxPower(arg0, func_0023FBD8(arg0));
                func_002113C0(arg0, 0xD, 1, 1);
            }
            func_002113C0(arg0, 0, 0x1000, 0);
        }
        if (BtlMember_IsMaxPowerFull(arg0) != 0) {
            func_001F9D78(arg0, 0x42);
            func_00206958(arg0, 0x100);
            BtlMember_SubBlast(arg0, 0x186A0);
            if (func_0023F430(arg0) & 0x100) {
                func_0020FC38(arg0, 0x40);
            } else {
                func_0020FC38(arg0, 0x17);
            }
            func_00212DD8(arg0, 0x13);
            func_002113C0(arg0, 0, 0x800, 1);
            func_001FBE80(arg0, 4.0f, D_00386100);
            BtlChar_Vibrate(arg0, D_00386104, D_00386108);
            func_002113C0(arg0, 0x10, 0x40000, 1);
            func_00211418(arg0, 0x200);
        }
        break;
    case 0x42:
        func_001F9FB0(arg0, 0);
        if (!(func_0023F410(arg0) & 0x10) && (func_001FA1D0(arg0, 0.25f) != 0)) {
            func_002113C0(arg0, 3, 0x10000, 1);
        }
        func_002113C0(arg0, 0xD, 1, 1);
        break;
    }

    f20 = D_0038610C;
    func_00215068(arg0, 5, 0xC, D_00386110, D_0038610C);
    func_00215E88(f20, arg0, 7);
    func_00216208(arg0, 0.0f, D_00386114);
    func_00216678(arg0);
    func_002113C0(arg0, 1, 0x400, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
    if (func_00211310(arg0, 0, 4) != 0) {
        func_002113C0(arg0, 0, 2, 0);
    }
}
