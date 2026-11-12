#include "common.h"

s32 func_002F95C8(u8 *arg0);
void func_002F9C80(u8 *arg0);
void func_002FB158(u8 *arg0, u8 *arg1);
u8 *strcpy(u8 *arg0, u8 *arg1);

s32 func_002F98F0(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 var_s0;
    s32 var_v0;

    if ((*(s8 *)arg0 != 0) || (func_002F9C80(arg0), var_v0 = 0, (*(s8 *)arg0 != 0))) {
        func_002FB158(arg0, arg1);
        var_s0 = func_002F95C8(arg0);
        if (var_s0 == 0) {
            func_002F9C80(arg0);
            var_v0 = func_002F95C8(arg0);
            var_s0 = var_v0;
            if (var_s0 != 0) {
                strcpy(arg1, arg2);
                goto block_5;
            }
        } else {
block_5:
            var_v0 = var_s0;
        }
    }
    return var_v0;
}
