#include "common.h"

s32 func_002BFF40(s32 arg0);
void func_002BFF88(s32 arg0, s32 arg1, s32 arg2);
void func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002D3078();

void func_002BFE98(s32 arg0, s32 arg1) {
    s32 var_a2;

    if (func_002BFF40(arg1) != 0) {
        func_002C2FF0(arg0, 0xFF000408);
        return;
    }
    var_a2 = 0;
    if (func_002D3078(arg0, 1) == 0) {
        var_a2 = 1;
        if (func_002D3078(arg0, 2, 0) == 0) {
            var_a2 = (func_002D3078(arg0, 3, 1) != 0) ? 2 : 0;
        }
    }
    func_002BFF88(arg0, arg1, var_a2);
}
