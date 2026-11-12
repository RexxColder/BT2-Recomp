#include "common.h"

s32 strcmp(void *arg0, void *arg1);

void func_00270348(void *arg0, void *arg1, s32 arg2) {
    s32 var_s1;
    u32 var_s2;
    u8 *temp_s3;
    u8 *var_s0;

    temp_s3 = *(u8 **)arg0 + (*(s32 *)arg1 * 0xC0);
    *(s32 *)(temp_s3 + 0x74) = arg2;
    *(s32 *)(temp_s3 + 0x48) = *(s32 *)(temp_s3 + 0x48) | 1;
    var_s1 = *(s32 *)((u8 *)arg1 + 4);
    var_s2 = 1;
    if (var_s1 != 0) {
        if ((u32)(*(s32 *)((u8 *)arg0 + 4) - *(s32 *)arg1) > 1U) {
            var_s0 = temp_s3 + 0xC0;
loop_3:
            if ((strcmp(var_s0, temp_s3) != 0)
                || (var_s1 -= 1, *(s32 *)(var_s0 + 0x74) = arg2,
                    *(s32 *)(var_s0 + 0x48) = *(s32 *)(var_s0 + 0x48) | 1, (var_s1 != 0))) {
                var_s2 += 1;
                var_s0 += 0xC0;
                if (var_s2 < (u32)(*(s32 *)((u8 *)arg0 + 4) - *(s32 *)arg1)) {
                    goto loop_3;
                }
            }
        }
    }
}
