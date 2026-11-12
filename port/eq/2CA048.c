#include "common.h"

void func_002CA0F8(void *arg0);
void func_002D0DD8(void *arg0, s32 arg1);

void func_002CA048(void *arg0, s32 *arg1, s32 arg2) {
    u8 *var_s0;
    s32 *var_s2;
    s32 var_s1;

    var_s0 = (u8 *)arg0;
    if (arg2 > 0) {
        var_s2 = arg1;
        var_s1 = arg2;
        do {
            *(s32 *)(var_s0 + 0) = 0;
            *(s32 *)(var_s0 + 4) = 0;
            var_s1 -= 1;
            func_002D0DD8(var_s0 + 0xC, 0);
            *(s32 *)(var_s0 + 0x38) = 0;
            *(s32 *)(var_s0 + 8) = *var_s2;
            var_s2 += 1;
            *(s32 *)(var_s0 + 0x3C) = 1;
            *(s32 *)(var_s0 + 0x40) = 0;
            *(s32 *)(var_s0 + 0x44) = 0;
            *(s32 *)(var_s0 + 0x48) = 0;
            *(s32 *)(var_s0 + 0x4C) = 0;
            *(s32 *)(var_s0 + 0x50) = 0;
            *(s32 *)(var_s0 + 0x58) = -1;
            func_002CA0F8(var_s0 + 0x5C);
            *(s32 *)(var_s0 + 0xE8) = 0;
            var_s0 += 0xF0;
        } while (var_s1 != 0);
    }
}
