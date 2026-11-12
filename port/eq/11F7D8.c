#include "common.h"

s32 func_0011FBC8(s32 arg0, s32 arg1);
s32 func_0011F408(s32 arg0, s32 arg1);
void func_0011F1E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 EftObj_UpdateMtx();
s32 func_0011ECA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0011EF10(s32 arg0, s32 arg1, s32 arg2);
s32 func_0011F370(s32 arg0, s32 arg1);
s32 func_0011F248(s32 arg0, s32 arg1);
void func_0011FD48(s32 arg0);
void func_0011FD78(s32 arg0);
s32 func_0020A658(s32 arg0);
s32 func_0011ED28(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 *D_003876FC;

s32 func_0011F7D8(s32 arg0, s32 arg1, s32 arg2) {
    s32 s0;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 s5;
    s32 a1;
    s32 a2x;
    s32 a3;
    s32 a2_2;
    s32 t_a3;
    s32 inc;
    s32 v0;
    s32 v1;
    s32 v0res;
    s32 u6;
    s32 res;

    s0 = arg0 + 0x38;
    s4 = *(s32 *)(D_003876FC + 0xC);

    a1 = *(s32 *)s0;
    if (a1 == -1) {
        v0 = func_0011FBC8(arg0, -1);
        if (v0 == 0) {
            return 0;
        }
        a1 = *(s32 *)s0;
    }
    if (a1 >= 0xED) {
        return func_0011F408(arg0, a1);
    }
    if (a1 >= *(s32 *)s4) {
        return 0;
    }

    a3 = *(s32 *)(s0 + 0x110);
    s2 = a3;
    s3 = 0;
    if (a3 == -1) {
        func_0011F1E0(arg0, a1, arg2, a3);
        a3 = *(s32 *)(s0 + 0x110);
        if (a3 == s2) {
            return 1;
        }
        a1 = *(s32 *)s0;
        if (a1 == s2) {
            return 0;
        }
        if (a1 >= 0xED) {
            return 1;
        }
    }

    /* L1F88C: the update of the table entry at index a1 */
    v1 = *(s32 *)(s4 + 8);
    a2x = *(s32 *)(s4 + 4);
    t_a3 = *(s32 *)(v1 + a1 * 4);
    s5 = *(s32 *)(a2x + a1 * 4);
    inc = *(s32 *)(s0 + 0x114) + 1;
    *(s32 *)(s0 + 0x114) = inc;
    s2 = t_a3 + a3 * 12;
    s3 = 0;
    v0res = EftObj_UpdateMtx(arg0, inc, a2x, t_a3);
    a2_2 = (s16)*(s16 *)(s2 + 8);
    if (a2_2 >= 0) {
        s3 = (func_0011ECA8(arg0, v0res, a2_2, *(u16 *)(s2 + 6)) != 0);
    } else if (func_0011EF10(arg0, s2, a2_2) != 0) {
        s3 = 1;
    }

    u6 = *(u16 *)(s2 + 6);
    if (func_0011F370(arg0, u6) != 0) {
        func_0011FD48(arg0);
    } else {
        u6 = *(u16 *)(s2 + 6);
        if (func_0011F248(arg0, u6) != 0) {
            func_0011FD78(arg0);
        } else if (s3 != 0) {
            v1 = *(s32 *)(s0 + 0x110) + 1;
            *(s32 *)(s0 + 0x114) = 0;
            *(s32 *)(s0 + 0x118) = 0;
            *(s32 *)(s0 + 0x110) = v1;
            *(s32 *)(s0 + 0x11C) = (s16)*(s16 *)(s2 + 8);
            if (v1 >= s5) {
                *(s32 *)(s0 + 0x110) = -1;
            }
        } else {
            v1 = EftObj_UpdateMtx(arg0);
            if (func_0011ECA8(arg0, v1, *(s32 *)(s0 + 0x11C), 0x10) == 0) {
                if (func_0020A658(*(s32 *)arg0) == 0) {
                    v1 = *(s32 *)(s0 + 0x118) + 1;
                    *(s32 *)(s0 + 0x118) = v1;
                    if (v1 > 0x1E) {
                        func_0011FD48(arg0);
                    }
                }
            }
        }
    }

    /* L1F9E0 */
    v0 = *(s32 *)s0;
    if (v0 == -1) {
        return 1;
    }
    a1 = *(s32 *)(s0 + 0x110);
    if (a1 == -1) {
        return 1;
    }
    v1 = *(s32 *)(s4 + 8);
    a2x = *(s32 *)(s0 + 0x114);
    t_a3 = *(s32 *)(v0 * 4 + v1);
    res = func_0011ED28(t_a3 + (a1 * 3) * 4, *(s32 *)(arg0 + 0x28), a2x, *(s32 *)(arg0 + 8));
    *(s32 *)(arg0 + 0x14) = res;
    return 1;
}
