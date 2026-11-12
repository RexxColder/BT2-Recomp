#include "common.h"

s32 func_002C2E48(s32 arg0);
void func_002C3238(s32 arg0, s32 arg1);
void func_002C3268(s32 arg0, s32 arg1);
void func_002C32A0(s32 arg0, s32 arg1);
extern s32 D_00346E4C __attribute__((section(".data")));
extern u8 D_0037A1D0[] __attribute__((section(".data")));
extern u8 *D_00395114 __attribute__((section(".data")));

s32 func_002C2DE0(s32 arg0) {
    s32 var_v0;

    D_00395114 = D_0037A1D0;
    D_00346E4C = 0x37B0;
    func_002C3238(0x37B0, 0x00340000);
    var_v0 = func_002C2E48(arg0);
    if (var_v0 == 0) {
        func_002C3268(arg0, 0x00340000);
        func_002C32A0(arg0, 0x00340000);
        var_v0 = 0;
    }
    return var_v0;
}
