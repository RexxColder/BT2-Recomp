#include "common.h"

extern s32 func_00211288(s32 arg0);
extern s32 func_0020A658(s32 arg0);
extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00241F80(s32 arg0, s32 arg1);
extern s32 func_00203C58(s32 arg0, s64 arg1);
extern s32 BtlMember_IsHealthEmpty_2127F8(s32 arg0);
extern u8 *BtlMember_GetActiveGauge(s32 arg0);
extern void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_00212820(s32 arg0);
extern s32 BtlObjXf_Update(s32 arg0);
extern s32 func_001FA3A8(s32 arg0);
extern s32 EftHit_GetHitCount(s32 arg0);
extern void func_00203968(s32 arg0, s32 arg1);
extern void func_00212DD8(s32 arg0, s32 arg1);

/* Decides whether a member consumes a guard/counter reaction for an incoming hit record:
   inspects the attacker link (state 0..1 or 2..4), then spends a charge counter and queues
   the matching flag. Returns 1 when a reaction was started. */
s32 func_00202088(s32 a0, u8 *hit) {
    s32 self = func_00211288(a0);
    u8 *self_p = (u8 *)self;
    s32 strong = 0;
    s32 power = 0;
    s32 *link;
    s32 state;
    s32 attacker;

    if (func_0020A658(a0)) {
        return 1;
    }
    if (*(s32 *)(hit + 0xC) == 0) {
        return func_00211310(self, 3, 2) != 0;
    }
    link = *(s32 **)(hit + 0x64);
    if (link == 0) {
        return 0;
    }
    state = link[1];
    attacker = func_00211288(link[0]);
    if (*(s32 *)(hit + 0x64) != 0 && state >= 0) {
        if (state < 2) {
            if (func_00211310(self, 3, 8)) {
                return 1;
            }
            if (func_00241F80(attacker, state) & 0x400000) {
                strong = 1;
            }
        } else if (state < 5) {
            if (func_00211310(self, 3, 4)) {
                return 0;
            }
            strong = 1;
            power = 1;
        }
    }
    if (func_00203C58(self, 0x100000000LL) && !BtlMember_IsHealthEmpty_2127F8(self) &&
        func_00211310(self, 0, 0x4000) && BtlMember_GetActiveGauge(self)[0x2B] && strong) {
        func_002113C0(self, 4, 0x80000000, 1);
        func_002113C0(self, 0, 0x4000, 0);
        return 1;
    }
    if (!func_00212820(self)) {
        return 0;
    }
    if (!(func_001FA3A8(BtlObjXf_Update(self)) & 0x10031)) {
        return 0;
    }
    if (EftHit_GetHitCount((s32)hit) != 0) {
        return 0;
    }
    if (!strong) {
        return 0;
    }
    if (*(s32 *)(self_p + 0x1168) > 0) {
        func_002113C0(self, 4, 0x80000000, 1);
        func_00203968(self, 50000);
        if (func_00203C58(self, 0x20000) && power) {
            func_00203968(self, 50000);
        }
        func_00212DD8(self, 31);
        func_002113C0(self, 16, 0x800000, 1);
        return 1;
    }
    if (*(s32 *)(self_p + 0xAC8) > 0) {
        *(s32 *)(self_p + 0xAC8) = *(s32 *)(self_p + 0xAC8) - 1;
        func_002113C0(self, 4, 0x80000000, 1);
        if (*(s32 *)(self_p + 0xAD0) == 0) {
            func_002113C0(self, 15, 0x400, 1);
        } else if (*(s32 *)(self_p + 0xAD0) == 1) {
            func_002113C0(self, 15, 0x800, 1);
        }
        return 1;
    }
    if (*(s32 *)(self_p + 0xACC) > 0) {
        *(s32 *)(self_p + 0xACC) = *(s32 *)(self_p + 0xACC) - 1;
        func_002113C0(self, 4, 0x80000000, 1);
        if (*(s32 *)(self_p + 0xAD0) == 0) {
            func_002113C0(self, 15, 0x400, 1);
        } else if (*(s32 *)(self_p + 0xAD0) == 1) {
            func_002113C0(self, 15, 0x800, 1);
        }
        return 1;
    }
    return 0;
}
