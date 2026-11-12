#include "common.h"

typedef void (*Fn3)(void *arg0, s32 arg1, s32 arg2);
void *func_002D07B0(void *arg0, s32 arg1);
s32 func_002DA3A8(void *arg0, s32 arg1, s32 arg2);
void func_002C2710(void *arg0);
void func_002C2D30(void *arg0);
void func_002C2548(void *arg0);

s32 func_002C2480(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *s3;
    Fn3 temp_s0;
    void *temp_a0;
    s32 s0v;
    s32 var_v0;

    s3 = arg0 + 0x78;
    temp_s0 = (Fn3)func_002D07B0(arg0, 0x4B);
    temp_a0 = func_002D07B0(arg0, 0x4C);
    if (temp_s0 != NULL) {
        temp_s0(temp_a0, arg1, arg2);
    }
    var_v0 = 0;
    if (*(s32 *)(arg0 + 0x78) == 0) {
        s0v = (arg2 < 0x801) ? arg2 : 0x800;
        func_002DA3A8(arg0 + 0x10C, arg1, s0v);
        *(s32 *)(s3 + 0x90) = s0v;
        func_002C2710(s3);
        func_002C2D30(arg0);
        func_002C2548(arg0);
        var_v0 = 1;
    }
    return var_v0;
}
