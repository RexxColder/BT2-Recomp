#include "common.h"

s32 Gsc_FindOptionN(s32 arg0, s32 arg1);
s32 Gsc_GetInt(void);
void func_002A3DD8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, s32 t1, s32 t2, s32 t3, s32 sp0);

s32 func_002A7308(s32 arg0) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_s7;
    s32 var_s7;

    if (arg0 == 0) {
        var_s7 = 0;
        while (Gsc_FindOptionN(0x64, var_s7) != 0) {
            temp_s6 = Gsc_GetInt();
            if (temp_s6 >= 0) {
                temp_s7 = Gsc_GetInt();
                temp_s5 = Gsc_GetInt();
                temp_s4 = Gsc_GetInt();
                temp_s3 = Gsc_GetInt();
                temp_s2 = Gsc_GetInt();
                temp_s1 = Gsc_GetInt();
                temp_s0 = Gsc_GetInt();
                func_002A3DD8(var_s7, temp_s6, temp_s7, temp_s5, temp_s4, temp_s3, temp_s2, temp_s0, temp_s0);
            }
            var_s7 += 1;
        }
    }
    return 1;
}
