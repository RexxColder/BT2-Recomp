#include "common.h"

void func_00102338(s32 arg0);
s32 func_00102350(void);
void func_0029F250();
s32 func_0029F6F8(s32 arg0);
s32 func_00100FC8(s32 arg0);
s32 Gsc_StartAction(s32 arg0, s32 arg1);

s32 func_002AB6F8(s32 *arg0) {
    s32 temp_v1;
    s32 var_v0;
    s32 *temp_s0;

    temp_v1 = arg0[0];
    if (temp_v1 == 0) {
        temp_s0 = (s32 *)arg0[1];
        func_00102338((s32)arg0);
        temp_s0[4] = Gsc_StartAction(temp_s0[3], 0x3E8);
        while (func_0029F6F8(temp_s0[4]) != 0) {
            func_0029F250();
        }
        if (func_00102350() == 0) {
            var_v0 = 1;
        } else {
            func_00100FC8(1);
            arg0[0] = arg0[0] + 1;
            var_v0 = 0;
        }
        return var_v0;
    }
    if (temp_v1 == 1) {
        if (func_00100FC8(0) == 0) {
            return 0;
        }
        return 1;
    }
    return 1;
}
