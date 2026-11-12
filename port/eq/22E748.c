#include "common.h"

extern f32 D_00386720;
extern f32 D_00386724;
extern f32 D_00386728;
extern f32 D_0038672C;
extern f32 D_00386730;
extern f32 D_00386734;
extern f32 D_00386738;
extern f32 D_0038673C;
extern f32 D_00386740;
extern f32 D_00386744;
extern f32 D_00386748;

void func_001FA110(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 BtlObjXf_Update(s32 arg0);
s32 func_00227DA0(s32 arg0, s32 arg1);
void func_001F9D78(void *arg0, s32 arg1);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216770(s32 arg0);
void func_00216890(s32 arg0, f32 farg0, f32 farg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00206958(s32 arg0, s64 arg1);
s32 BtlMember_GetActiveGauge(s32 arg0);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 BtlMember_IsHealthEmpty_2127F8(s32 arg0);
s32 func_00203118(s32 arg0);

/* 0x0022E748 (battle member state dispatch). After a common prologue (a blend update when func_00227DA0 changes the
 * route) the switch on BtlObjXf_Update's result (227..233, jtbl_00370750) runs one of three arms; the 230/231 and
 * 232/233 arms set the flag that enables the health/counter block at the end. Common tail: four
 * func_002113C0 calls, then the active-gauge check and the counter at obj+0x8C0 (increments, sets bit 1 of
 * obj+0x8DC once it reaches 0x1F). */
void func_0022E748(u8 *obj) {
    s32 self = (s32)obj;
    s32 state;
    s32 route;
    s32 flag = 0;
    s32 count;
    u8 *gauge;

    func_001FA110(self, 0);
    if (func_00211310(self, 2, 0x200) == 0) {
        state = BtlObjXf_Update(self);
        route = func_00227DA0(self, state);
        if (state != route) {
            func_001F9D78(obj, route);
            BtlAnim_SetBlend(self, D_00386720);
        }
    }

    state = BtlObjXf_Update(self);
    switch (state) {
    case 0xE3:
    case 0xE4:
        func_00215068(self, 5, 0xC, D_00386734, D_00386730);
        func_00215E88(D_00386730, self, 7);
        func_00216208(self, 0.0f, D_00386738);
        func_00216770(self);
        if (func_00211310(self, 0, 4) != 0) {
            func_00206958(self, 0x1000000000LL);
        }
        break;

    case 0xE6:
    case 0xE7:
        func_00215068(self, 5, 0xC, D_00386728, D_00386724);
        func_00215E88(D_00386724, self, 7);
        func_00216208(self, 0.0f, D_0038672C);
        flag = 1;
        func_00216770(self);
        break;

    case 0xE8:
    case 0xE9:
        func_00215068(self, 5, 0xC, D_00386740, D_0038673C);
        func_00215E88(D_0038673C, self, 7);
        func_00216208(self, 0.0f, D_00386744);
        flag = 1;
        func_00216890(self, D_00386748, D_00386744);
        break;

    default:
        break;
    }

    func_002113C0(self, 1, 0x400000, 1);
    func_002113C0(self, 0x10, 0x100000, 1);
    gauge = (u8 *)BtlMember_GetActiveGauge(self);
    if (*(u8 *)(gauge + 0x29) != 0) {
        func_002113C0(self, 6, 8, 1);
        func_002113C0(self, 0xF, 1, 1);
        if (BtlPad_Test4C(self, 0x18) != 0) {
            *(s32 *)(obj + 0xB94) -= 1;
        }
    }

    if (flag != 0 && BtlMember_IsHealthEmpty_2127F8(self) != 0 && func_00211310(self, 0xA, 0x10) == 0 &&
        func_00203118(self) > 0) {
        count = *(s32 *)(obj + 0x8C0) + 1;
        *(s32 *)(obj + 0x8C0) = count;
        if (count >= 0x1F) {
            *(s32 *)(obj + 0x8DC) |= 1;
        }
    }
}
