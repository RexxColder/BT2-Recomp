#include "common.h"

extern s32 BtlObjXf_Update(s32 arg0);
extern s32 func_00212878(void);
extern f32 BtlMember_GetHealthRatio(s32 arg0);
extern void func_001FA110(s32 arg0, s32 arg1);
extern s32 func_00212820(s32 arg0);
extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 BtlPad_Test48(s32 arg0, s32 arg1);
extern s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00218838(s32 arg0, s32 arg1);
extern void func_00217238(s32 arg0, s32 arg1);
extern void func_00206958(s32 arg0, s64 arg1);
extern void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
extern void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
extern void func_00216208(f32 farg0, f32 farg1, s32 arg0);
extern void BtlMove_BrakeVertical(s32 arg0);
extern void func_00216678(s32 arg0);
extern void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_001F9FB0(s32 arg0, s32 arg1);
extern f32 D_00386008;
extern f32 D_0038600C;
extern f32 D_00386010;
extern f32 D_00386014;
extern f32 D_00386018;

/* Aerial-move state step: the state switch (204..209, 251/252) picks the next sub-state and
   scales/replaces the two float params, then the shared tail applies movement and flags. */
void func_00221FE0(u8 *self) {
    s32 obj = (s32)self;
    s32 *cnt = (s32 *)(self + 0x8C0);
    s32 braking = 1;
    f32 f21 = D_00386008;
    f32 f22 = D_0038600C;
    s32 state = BtlObjXf_Update(obj);
    s32 next;

    switch (state) {
    case 204:
        func_001FA0A0(obj, 205, 0);
        func_00206958(obj, 0x100000000000LL);
        break;
    case 207:
        func_001FA0A0(obj, 208, 0);
        func_00206958(obj, 0x100000000000LL);
        break;
    case 205:
    case 208:
        if (func_00212878()) {
            f32 hr = BtlMember_GetHealthRatio(obj);
            f21 = f21 * ((1.0f - hr) * 0.5f + 0.5f);
        }
        if (*cnt > 0) {
            func_001FA110(obj, 0);
            *cnt = *cnt - 1;
        } else {
            next = 206;
            if (BtlObjXf_Update(obj) != 205) {
                next = 209;
            }
            if (func_00212820(obj)) {
                if (!func_00211310(obj, 1, 0x40000)) {
                    if (BtlPad_Test48(obj, 8) || func_00212878()) {
                        next = 251;
                        if (BtlObjXf_Update(obj) != 205) {
                            next = 252;
                        }
                    }
                }
            }
            func_001FA0A0(obj, next, 0);
        }
        if (*(s32 *)(self + 0x8CC) > 0) {
            func_00217238(obj, func_00218838(obj, 0));
        }
        func_00206958(obj, 0x100000000000LL);
        break;
    case 206:
    case 209:
        func_001F9FB0(obj, 0);
        braking = 0;
        break;
    case 251:
    case 252:
        func_001F9FB0(obj, 0);
        func_002113C0(obj, 0, 2, 1);
        f21 = 0.0f;
        f22 = D_00386010;
        break;
    default:
        break;
    }

    func_00215068(obj, 5, 13, D_00386018, D_00386014);
    if (func_00218838(obj, 0)) {
        func_00215E88(D_00386014, obj, 3);
    } else {
        func_00215E88(D_00386014, obj, 5);
    }
    func_00216208(f21, f22, obj);
    if (braking) {
        BtlMove_BrakeVertical(obj);
    } else {
        func_00216678(obj);
    }
    func_002113C0(obj, 9, 0x200, 1);
    func_002113C0(obj, 1, 0x800, 1);
    func_002113C0(obj, 6, 4, 1);
    func_002113C0(obj, 6, 8, 1);
    if (func_00211310(obj, 0, 0x100)) {
        func_002113C0(obj, 0, 2, 1);
    }
}
