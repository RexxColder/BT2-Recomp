#include "common.h"

/* GUESS arity: func_00208DE8 gets a fourth argument (a3 = arg2 < 2) in the calls that leave it set */
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
s32 func_00312FB0(f32 farg0, s32 arg0, s32 arg1);

void func_00197030(s32 arg0, s32 arg1, s32 arg2) {
    u8 fr[0x20];
    s32 var_a2;
    s32 temp_a3;

    var_a2 = 3;
    temp_a3 = arg2 < 2;
    if (arg2 == 1) {
        func_00208DE8(arg1, arg0, var_a2, temp_a3);
        return;
    }
    if (temp_a3 == 0) {
        if (arg2 != 2) {
            return;
        }
        func_00208DE8(arg1, (s32)fr, 0xA, temp_a3);
        func_00208DE8(arg1, (s32)(fr + 0x10), 0xE, 0);
        func_00312638(arg0, (s32)fr, (s32)(fr + 0x10));
        func_00312FB0(0.5f, arg0, arg0);
        return;
    }
    if (arg2 != 0) {
        return;
    }
    var_a2 = 0x11;
    func_00208DE8(arg1, arg0, var_a2, temp_a3);
}
