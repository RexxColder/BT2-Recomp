#include "common.h"

void func_002E73E0(s32 arg0);
s32 func_002E7580(s32 arg0, s32 arg1, s32 arg2);
s32 func_002E8828(s32 arg0, s32 arg1, s32 arg2);
s32 func_002E8A98(s32 arg0, s32 arg1);
s32 func_002E8CF0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002E92A0(s32 arg0, s32 arg1);
s32 func_003084A8(s32 arg0, s32 arg1, s32 arg2);
s32 func_00308558(s32 arg0, s32 arg1);
s32 func_00308A60(s32 arg0, s32 arg1);
s32 func_00308BD8(s32 arg0, s32 arg1, s32 arg2);
s32 func_00309368(s32 arg0, s32 arg1);
s32 func_003094D0(s32 arg0, s32 arg1, s32 arg2);

s32 func_002E7918(s32 arg0, u8 *arg1, s32 arg2) {
    u16 temp_v0;

    func_002E73E0(arg0);
    temp_v0 = *(u16 *)arg1;
    if ((((temp_v0 >> 8) | (temp_v0 << 8)) & 0xFFFF) == 0x8000) {
        return func_002E7580(arg0, (s32)arg1, arg2);
    }
    if (func_002E8A98((s32)arg1, (s32)arg1) != 0) {
        return func_002E8828(arg0, (s32)arg1, arg2);
    }
    if (func_002E92A0((s32)arg1, (s32)arg1) != 0) {
        return func_002E8CF0(arg0, (s32)arg1, arg2);
    }
    if (func_00308A60((s32)arg1, (s32)arg1) != 0) {
        return func_00308BD8(arg0, (s32)arg1, arg2);
    }
    if (func_00309368((s32)arg1, (s32)arg1) != 0) {
        return func_003094D0(arg0, (s32)arg1, arg2);
    }
    if (func_00308558((s32)arg1, (s32)arg1) != 0) {
        return func_003084A8(arg0, (s32)arg1, arg2);
    }
    return -1;
}
