#include "common.h"

s32 func_002C3210(s32 arg0);
s32 func_002C2FF0(s32 arg0, s32 arg1);
void func_002C2308(s32 arg0);
void func_002BFB70(s32 arg0);
s32 func_002CE5A0(s32 arg0);
void func_002CE6D8(s32 arg0);
extern u8 D_00346E2C[] __attribute__((section(".data")));

s32 func_002CE500(s32 arg0) {
    u8 *var_v1;
    s32 temp_a1;
    s32 var_a0;

    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000131);
    }
    func_002CE6D8(arg0);
    func_002C2308(arg0 + 0x78);
    func_002BFB70(arg0);
    var_a0 = 7;
    temp_a1 = func_002CE5A0(arg0);
    var_v1 = D_00346E2C;
    do {
        if (*(s32 *)var_v1 == arg0) {
            *(s32 *)var_v1 = 0;
        }
        var_a0 -= 1;
        var_v1 += 4;
    } while (var_a0 >= 0);
    return temp_a1;
}
