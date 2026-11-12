#include "common.h"

void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void *func_001EA418(void);
void func_001EA480(void *arg0, void *arg1, void *arg2);

void *func_001E9610(u8 *arg0) {
    s32 var_s2;
    u8 *var_v0;

    var_s2 = 0;
    if (*(s32 *)(arg0 + 0x110) > 0) {
loop_2:
        var_v0 = func_001EA418();
        if (var_v0 != NULL) {
            var_s2 += 1;
            func_00129BD0(var_v0, arg0 + 0x70, *(f32 *)(arg0 + 0xC4));
            *(s16 *)(var_v0 + 0x14) = 1;
            *(s32 *)(var_v0 + 0x18) = 0;
            *(s32 *)(var_v0 + 0x1C) = 0;
            func_001EA480(arg0 + 0x180, arg0 + 0x184, var_v0);
            *(s32 *)(arg0 + 0x114) = *(s32 *)(arg0 + 0x114) + 1;
            if (var_s2 >= *(s32 *)(arg0 + 0x110)) {
                goto block_4;
            }
            goto loop_2;
        }
    } else {
block_4:
        var_v0 = (u8 *)1;
    }
    return var_v0;
}
