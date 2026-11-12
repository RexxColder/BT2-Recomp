#include "common.h"

s32 Gsc_GetInt(s32 arg0);
void func_002A3B48(s32 arg0, s32 arg1, s32 arg2);
void func_0025B9C8(s32 arg0, s32 arg1);

s32 func_002A5E30(s32 arg0) {
    s32 sp[4];
    s32 sp10[4];
    s32 temp_v0;

    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt(arg0);
        if (temp_v0 >= 0) {
            func_002A3B48(temp_v0, (s32)sp, (s32)sp10);
            func_0025B9C8((s32)sp, (s32)sp10);
        }
    }
    return 1;
}
