#include "common.h"

s32 BtlMember_GetActiveGauge(s32 arg0);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
void func_001FA110(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212820(s32 arg0);
void func_00215068(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(f32 farg0, f32 farg1, s32 arg0);
void func_00216770(s32 arg0);
s32 func_0023F410(s32 arg0);
extern f32 D_00386760;
extern f32 D_00386764;
extern f32 D_00386768;

void func_0022EC48(s32 arg0) {
    f32 temp_f20;
    s32 gauge;

    temp_f20 = D_00386760;
    func_001FA110(arg0, 0);
    func_00215068(D_00386764, temp_f20, arg0, 5, 0xC);
    func_00215E88(temp_f20, arg0, 7);
    func_00216208(0.0f, D_00386768, arg0);
    func_00216770(arg0);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 0x10, 0x100000, 1);
    gauge = BtlMember_GetActiveGauge(arg0);
    if (*(u8 *)(gauge + 0x29) != 0) {
        func_002113C0(arg0, 6, 8, 1);
        if ((func_00212820(arg0) != 0) && (func_00211310(arg0, 1, 0x40000) == 0) &&
            !(func_0023F410(arg0) & 0x1000)) {
            func_002113C0(arg0, 0xF, 1, 1);
            if (BtlPad_Test4C(arg0, 0x18) != 0) {
                *(s32 *)(arg0 + 0xB94) = *(s32 *)(arg0 + 0xB94) - 1;
            }
        }
    }
    if (func_0023F410(arg0) & 0x1000) {
        func_002113C0(arg0, 1, 0x02000000, 1);
    }
}
