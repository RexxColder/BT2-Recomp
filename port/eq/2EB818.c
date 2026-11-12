#include "common.h"

void func_002EA2F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002EB500(void);
s32 func_002EB730(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002EBB38(s32 arg0);

s32 func_002EB818(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_a0;
    s32 var_s2;

    func_002EA2F0(1, 0, arg0, arg1, -1);
    var_s2 = func_002EB500();
    if (var_s2 != 0) {
        if (func_002EB730(var_s2, arg0, arg1, arg2, arg3) < 0) {
            temp_a0 = var_s2;
            var_s2 = 0;
            func_002EBB38(temp_a0);
        }
    }
    func_002EA2F0(1, 1, arg0, arg1, -1);
    return var_s2;
}
