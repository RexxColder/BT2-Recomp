#include "common.h"

void func_002EEAC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_0030A760(s32 arg0);
extern s32 D_0035349C __attribute__((section(".data")));

s32 func_002EF918(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_s0;

    var_s0 = 1;
    if (D_0035349C == 1) {
        var_s0 = 1;
    } else if ((D_0035349C == 0) || (D_0035349C == 2)) {
        func_002EEAC0(arg0, arg1, arg2, arg3, arg4);
    } else {
        var_s0 = 0;
    }
    func_0030A760(-1);
    return var_s0;
}
