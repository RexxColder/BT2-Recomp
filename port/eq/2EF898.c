#include "common.h"

void func_002EE8E0(s32 arg0);
s32 func_002EF968(s32 arg0);
s32 func_0030A760(s32 arg0);
extern s32 D_0035349C __attribute__((section(".data")));

s32 func_002EF898(s32 arg0, s32 arg1) {
    s32 var_s1;

    var_s1 = 1;
    func_0030A760(func_002EF968(arg0));
    D_0035349C = arg0;
    switch (arg0) {
    case 1:
        break;
    default:
        var_s1 = 0;
        break;
    case 2:
    case 0:
        func_002EE8E0(arg1);
        break;
    }
    return var_s1;
}
