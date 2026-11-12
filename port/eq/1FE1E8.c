#include "common.h"

/* 0x001FE1E8 (2 args: a0 = battle result, a1 = member index). Summary from the asm:
   obj = func_00211288(a1). If 203C58(obj, 1<<32) && !IsHealthEmpty(obj) && 211310(obj,0,0x4000) && gauge[0x2B]:
   set bit 0x20000000 of word 4, clear 0x4000 of word 0, return 0.
   Else if 212820(obj) == 0: return 1. Else pulse via BtlObjXf_Update/1FA3A8 and the 0x10031 test;
   with the mask set: flag branch, then counters 0xAC8 / 0xACC; else tail on 211310(obj,3,0x8000). */
s32 func_00211288(s32 arg0);
s32 func_00203C58(s32 arg0, s64 arg1);
s32 BtlMember_IsHealthEmpty_2127F8(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
u8 *BtlMember_GetActiveGauge(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212820(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA3A8(s32 arg0);
s32 BattleResult_GetFlags(s32 arg0);
void func_00203968(s32 arg0, s32 arg1);
s32 func_0023F3D0(s32 arg0);
s32 func_0023FB20(s32 arg0);
void func_00203888(s32 arg0, s32 arg1, s32 arg2);

s32 func_001FE1E8(s32 arg0, s32 arg1) {
    s32 obj;
    s32 v;
    s32 n;
    u8 *gauge;

    obj = func_00211288(arg1);
    if (func_00203C58(obj, 0x100000000LL) != 0 && BtlMember_IsHealthEmpty_2127F8(obj) == 0
        && func_00211310(obj, 0, 0x4000) != 0) {
        gauge = BtlMember_GetActiveGauge(obj);
        if (gauge[0x2B] != 0) {
            func_002113C0(obj, 4, 0x20000000, 1);
            func_002113C0(obj, 0, 0x4000, 0);
            return 0;
        }
    }

    if (func_00212820(obj) == 0) {
        return 1;
    }

    v = func_001FA3A8(BtlObjXf_Update(obj));
    if ((v & 0x10031) != 0) {
        if (*(s32 *)((u8 *)obj + 0x1164) > 0 && (BattleResult_GetFlags(arg0) & 1) != 0) {
            func_002113C0(obj, 4, 0x20000000, 1);
            func_00203968(obj, 20000);
            func_002113C0(obj, 16, 0x800000, 1);
            *(s32 *)((u8 *)obj + 0x14A8) += 1;
            return 0;
        }

        n = *(s32 *)((u8 *)obj + 0xAC8);
        if (n > 0) {
            *(s32 *)((u8 *)obj + 0xAC8) = n - 1;
            func_002113C0(obj, 4, 0x20000000, 1);
            if (*(s32 *)((u8 *)obj + 0xAD0) == 0) {
                func_002113C0(obj, 15, 0x400, 1);
            } else if (*(s32 *)((u8 *)obj + 0xAD0) == 1) {
                func_002113C0(obj, 15, 0x800, 1);
            }
            return 0;
        }

        n = *(s32 *)((u8 *)obj + 0xACC);
        if (n > 0) {
            *(s32 *)((u8 *)obj + 0xACC) = n - 1;
            func_002113C0(obj, 4, 0x40000000, 1);
            if (*(s32 *)((u8 *)obj + 0xAD0) == 0) {
                func_002113C0(obj, 15, 0x400, 1);
            } else if (*(s32 *)((u8 *)obj + 0xAD0) == 1) {
                func_002113C0(obj, 15, 0x800, 1);
            }
            return 0;
        }
    }

    if (func_00211310(obj, 3, 0x8000) == 0) {
        return 1;
    }
    if (func_0023F3D0(arg0) != 4) {
        return 1;
    }
    func_002113C0(obj, 4, 0x20000000, 1);
    func_002113C0(obj, 16, 0x400000, 1);
    n = func_0023FB20(obj);
    func_00203888(obj, n, 0);
    return 0;
}
