#include "common.h"

void func_00129C28(void *arg0, s32 arg1);

void func_00162F98(s32 arg0_unused, s32 *arg1, s32 arg2) {
    u8 *s0;
    s32 var_s1;
    s32 temp_s2;

    s0 = (u8 *)arg1;
    if (!(*arg1 & 0x1000)) {
        var_s1 = 0;
        do {
            temp_s2 = var_s1 * 2;
            if ((*arg1 & (1 << temp_s2)) || (*arg1 & 1)) {
                func_00129C28(s0 + (var_s1 << 6) + 0x20, arg2);
            }
            if ((*arg1 & (1 << (temp_s2 + 1))) || (*arg1 & 1)) {
                func_00129C28(s0 + (var_s1 << 6) + 0x40, arg2);
            }
            var_s1 += 1;
        } while (var_s1 < 6);
    }
}
