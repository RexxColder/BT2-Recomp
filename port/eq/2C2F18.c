#include "common.h"

s32 func_002BF898(s32 arg0);
void func_002C3250(void);
void func_002C3288(void);
void func_002C32A8(void);
s32 func_002CE500(s32 arg0);
void func_002D0BB0(s32 arg0);
s32 func_002D2930(s32 arg0);
extern u8 D_00346DD8[] __attribute__((section(".data")));
extern u8 D_00346E2C[] __attribute__((section(".data")));

s32 func_002C2F18(void) {
    u8 *var_s1;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s2;
    u8 *p;

    var_s0 = 7;
    var_s1 = D_00346E2C;
    var_s2 = 0;
    do {
        temp_v0 = *(s32 *)var_s1;
        var_s1 += 4;
        if (temp_v0 != 0) {
            var_s2 = func_002CE500(temp_v0);
        }
        var_s0 -= 1;
    } while (var_s0 >= 0);
    p = D_00346DD8;
    func_002D0BB0((s32)p);
    func_002BF898((s32)(p + 0xC));
    var_s0 = func_002D2930((s32)(p + 0x10));
    func_002C32A8();
    func_002C3288();
    func_002C3250();
    return (var_s0 == 0) ? var_s2 : var_s0;
}
