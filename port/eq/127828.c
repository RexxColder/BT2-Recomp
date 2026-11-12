#include "common.h"

s32 func_00127638(void *arg0, void *arg1, s32 arg2, s32 arg3);

s32 func_00127828(void *arg0, void *arg1) {
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a2;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x8);
    temp_v0 = *(s32 *)((u8 *)arg1 + 0x8);
    temp_a3 = temp_v1 < temp_v0;
    var_a2 = 2;
    if (temp_v0 >= temp_v1) {
        var_a2 = 1;
        if (temp_a3 == 0 && (*(s32 *)((u8 *)arg0 + 0x68) == 0 || (var_a2 = 3, *(s32 *)((u8 *)arg1 + 0x68) == 0))) {
            var_a2 = func_00127638(arg0, arg1, var_a2, temp_a3);
        }
    }
    return var_a2;
}
