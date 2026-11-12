#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);
s32 func_002D3078(s32 arg0, s32 arg1);

s32 func_002CFC18(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 temp_v0;

    if (func_002D3078(arg0, 2) != 0) {
        temp_v0 = func_002D07B0(arg0, 5);
        if (temp_v0 == 1) {
            *arg2 = temp_v0;
            return *arg1 == 0;
        }
    }
    *arg2 = 0;
    return 0;
}
