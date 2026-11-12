#include "common.h"

extern u8 *D_00387A40;

s32 func_0020ADA0(s32 arg0);
s32 func_00101720(s32 arg0);
s32 Ramp_Step(u8 *arg0);
void func_0027ABE8(f32 arg0);
void func_00101700(s32 arg0);
s32 func_00267550(s32 arg0, s32 arg1, s32 arg2);

/* jtbl_0036C550: state 0,1 -> .L0010A068 (with func_0027ABE8 on the Ramp path),
 * 2,3 -> .L0010A0D0 (no func_0027ABE8), 4 -> .L0010A18C (returns 2), >= 5 -> common tail. */
s32 func_0010A030(u8 *arg0) {
    u8 st;
    s32 bump;
    s32 res;

    st = arg0[8];
    bump = 0;
    if (st == 4) {
        return 2;
    }
    if (st == 0 || st == 1) {
        if (func_0020ADA0(arg0[9]) != 0) {
            if (func_00101720(arg0[9]) == 5) {
                func_0027ABE8(1.0f);
                bump = 1;
            } else if (Ramp_Step(arg0 + 0x14) != 0) {
                func_0027ABE8(1.0f);
                bump = 1;
            }
        }
    } else if (st == 2 || st == 3) {
        if (func_0020ADA0(arg0[0xA]) != 0) {
            if (func_00101720(arg0[0xA]) == 5) {
                func_0027ABE8(1.0f);
                bump = 1;
            } else if (Ramp_Step(arg0 + 0x14) != 0) {
                bump = 1;
            }
        }
    }
    if (bump) {
        arg0[8] = (u8)(arg0[8] + 1);
    }

    if (*(s32 *)arg0 == 0) {
        return 1;
    }
    res = ((s32 (*)(s32))(*(s32 *)arg0))(*(s32 *)(arg0 + 4));
    if (res == 0) {
        return 1;
    }
    func_00101700(0);
    func_00101700(1);
    func_00267550(*(s32 *)D_00387A40, 0, 0);
    func_00267550(*(s32 *)D_00387A40 + 0x18580, 0, 0);
    return 2;
}
