#include "common.h"

s32 func_002F6AB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002C2D60(s32 arg0);
s32 func_002BE168(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_002BDD98(void);

void func_002BE0A8(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 sp[4];
    s32 var_a3;
    u8 *temp_s4;

    *arg3 = 0;
    temp_s4 = *(u8 **)((u8 *)arg0 + 0x2004);
    if (arg2 >= 0x120) {
        if (func_002F6AB8(arg1, arg2, (s32)sp, (s32)arg3) != 0) {
            var_a3 = sp[0];
        } else {
            var_a3 = 0;
            if (func_002C2D60(arg0) < 0x6C) {
                var_a3 = func_002BE168(arg0, arg1, arg2, 0) - arg1;
            }
        }
        *arg3 = var_a3;
        *(s32 *)(temp_s4 + 0x3C) = (s32)func_002BDD98;
        *(s64 *)((u8 *)arg0 + 0x9C8) = (s64)var_a3 + *(s64 *)((u8 *)arg0 + 0x9C8);
    }
}
