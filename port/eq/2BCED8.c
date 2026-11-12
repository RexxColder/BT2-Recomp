#include "common.h"

s32 func_002B61E0(void);
s32 func_002BC550(s32 arg0);
void func_002BCDF8(void);
void func_002BCE28(void);
void func_002BCE90(void);
void func_002BCFD0(s32 arg0);
void func_002BD180(s32 arg0);
s32 func_002BD298(void);
s32 func_002BD3A8(void);
s32 func_002CCE88(void);
extern s32 D_00345344 __attribute__((section(".data")));

s32 func_002BCED8(void) {
    s32 var_v0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_s2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s0;

    temp_s2 = D_00345344;
    var_v0 = 0;
    if (temp_s2 == 1) {
        temp_v0 = func_002B61E0();
        temp_v0_2 = func_002BC550(temp_v0 + 0x58);
        var_v0 = 0;
        if (temp_v0_2 == temp_s2) {
            func_002BCDF8();
            if (func_002BD3A8() != temp_v0_2) {
                var_s0 = temp_v0 + 0x6C;
                var_s1 = 7;
                do {
                    if (var_s0 != 0) {
                        func_002BCFD0(var_s0);
                    }
                    var_s1 -= 1;
                    var_s0 += 0x304;
                } while (var_s1 >= 0);
            }
            var_s1_2 = 0;
            func_002BD180(0);
            if (func_002BD3A8() != 1) {
                var_s1_2 = func_002CCE88() != 1;
            }
            func_002BCE28();
            var_v0 = var_s1_2;
            if (var_s1_2 != 1) {
                var_v0 = var_s1_2;
                if (func_002BD298() != 1) {
                    func_002BCE90();
                    var_v0 = var_s1_2;
                }
            }
        }
    }
    return var_v0;
}
