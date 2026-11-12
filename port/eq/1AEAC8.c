#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define UB(p, off) (*(u8 *)((u8 *)(p) + (off)))
#define FL(p, off) (*(f32 *)((u8 *)(p) + (off)))

extern f32 D_00384F2C;
extern s32 *D_00387858;

s32 BtlScene_IsCharStopped(s32 arg0);
s32 BtlTask_SetDead(void *arg0);
s32 func_00126528(void);
void func_00129C28(void *arg0, void *arg1);
s32 func_001AF140(void *arg0);
s32 func_001AF280(void *arg0);
void func_001AF500(void *arg0, void *arg1);
void func_001AF898(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_001AF9F0(void *arg0);
void func_001AFCD8(void *arg0, s32 arg1);
void func_001AFCE0(void *arg0);
void func_001AFCE8(void *arg0);
void func_001AFCF8(void *arg0);
void func_001AFD00(void *arg0);
void func_001B0488(void *arg0);
void func_001B05A0(void *arg0);
void func_001B06D0(f32 farg0, void *arg1, s32 arg2, s32 arg3);
void func_001B0728(f32 farg0, void *arg1);
void func_001B0C00(void *arg0);
s32 func_0020A540(s32 arg0);
s32 func_0020ABE0(s32 arg0);

void func_001AEAC8(void *arg0) {
    void *temp_s0;
    s32 var_s1;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    void *temp_a0;
    void *temp_a0_2;
    void *var_a1;
    s32 var_condition_bit;
    f32 temp_f0;
    f32 temp_f1;

    temp_s0 = *(void **)((u8 *)arg0 + 0x38);
    var_s1 = 0;
    if (UB(temp_s0, 0x5C) != 0) {
        if (W(temp_s0, 0x60) & 8) {
            temp_v1 = UB(arg0, 1);
            if (temp_v1 >= 2) {
                if (temp_v1 == 2) {
                    var_s1 = func_0020A540(W(temp_s0, 0x44)) != 0;
                }
            } else {
                var_s1 = func_0020ABE0(W(temp_s0, 0x44)) == 0;
                if (func_0020A540(W(temp_s0, 0x44)) != 0) {
                    var_s1 = 1;
                }
            }
            if ((var_s1 != 0) && !(W(temp_s0, 0x60) & 0x10)) {
                func_001B0C00(arg0);
                func_001AFCE0(temp_s0);
                UB(temp_s0, 0x5D) = 0;
                UB(temp_s0, 0x162) = 0;
                UB(arg0, 1) = 3;
                W(temp_s0, 0x60) = W(temp_s0, 0x60) | 0x10;
            }
            if (func_00126528() != 0) {
                return;
            }
            goto block_19;
        }
        if (BtlScene_IsCharStopped(W(temp_s0, 0x44)) == 0) {
block_19:
            temp_v1_2 = UB(arg0, 1);
            if (temp_v1_2 != 1) {
                if (temp_v1_2 >= 2) {
                    if (temp_v1_2 != 2) {
                        var_a1 = (u8 *)temp_s0 + 0x1C4;
                        if (temp_v1_2 == 3) {
                            var_a1 = (u8 *)temp_s0 + 0x1C4;
                            if (func_001AF280(temp_s0) != 0) {
                                func_001AFCE0(temp_s0);
                                func_001AFCF8(temp_s0);
                                BtlTask_SetDead(arg0);
                                *D_00387858 -= 1;
                                goto block_41;
                            }
                        }
                    } else {
                        if ((func_001AF140(temp_s0) == 1) || (W(arg0, 4) & 0x3F)) {
                            UB(temp_s0, 0x5D) = 0;
                            UB(temp_s0, 0x162) = 0;
                            UB(arg0, 1) = 3;
                        }
                        goto block_41;
                    }
                } else {
                    var_a1 = (u8 *)temp_s0 + 0x1C4;
                    if (temp_v1_2 == 0) {
                        func_001AFCD8(temp_s0, W(temp_s0, 0x40));
                        func_001AF898(temp_s0, 0.5f, 2.0f, FL(temp_s0, 0x74), 0.0f);
                        UB(temp_s0, 0x5D) = 1;
                        UB(arg0, 1) = 1;
block_41:
                        var_a1 = (u8 *)temp_s0 + 0x1C4;
                    }
                }
            } else {
                func_001B06D0(FL(temp_s0, 0x70), temp_s0, W(temp_s0, 0x44), W(temp_s0, 0x64));
                func_001AFCE8(temp_s0);
                func_001B0728(D_00384F2C, temp_s0);
                var_a1 = (u8 *)temp_s0 + 0x1C4;
                if (UB(temp_s0, 0x162) != 0) {
                    temp_v1_3 = UB(temp_s0, 0x161);
                    if (temp_v1_3 & 2) {
                        temp_f1 = FL(temp_s0, 0x154);
                        temp_f0 = FL(temp_s0, 0x150) + temp_f1;
                        FL(temp_s0, 0x150) = temp_f0;
                        if (temp_f1 > 0.0f) {
                            var_condition_bit = FL(temp_s0, 0x158) < temp_f0;
                        } else {
                            var_condition_bit = temp_f0 < FL(temp_s0, 0x158);
                        }
                        var_a1 = (u8 *)temp_s0 + 0x1C4;
                        if (var_condition_bit) {
                            FL(temp_s0, 0x150) = FL(temp_s0, 0x158);
                            UB(temp_s0, 0x161) = (u8)(temp_v1_3 & 0xFD);
                        }
                    }
                }
            }
            func_001AF500((u8 *)temp_s0 + 0x1C0, var_a1);
            func_001AF9F0(temp_s0);
            func_001AFD00(temp_s0);
            if (W(temp_s0, 0x60) & 1) {
                temp_a0 = *(void **)((u8 *)temp_s0 + 0x78);
                if (temp_a0 != NULL) {
                    func_00129C28(temp_a0, temp_s0);
                }
            }
            if (W(temp_s0, 0x60) & 2) {
                temp_a0_2 = *(void **)((u8 *)temp_s0 + 0x7C);
                if (temp_a0_2 != NULL) {
                    func_00129C28(temp_a0_2, (u8 *)temp_s0 + 0x30);
                }
            }
            if ((UB(temp_s0, 0x58) != 0) && (UB(arg0, 1) == 2)) {
                if (W(temp_s0, 0x174) != 0) {
                    func_001B05A0(arg0);
                    return;
                }
                func_001B0488(arg0);
            }
        }
    }
}
