#include "common.h"

s32 strlen(s32 arg0);
s32 strncmp(char *arg0, const char *arg1, u32 arg2);
extern u8 D_0039D93C[] __attribute__((section(".data")));

s32 func_002F95C8(s32 arg0) {
    s32 temp_s3;
    s32 var_s0;
    u32 var_s1;

    var_s1 = 0;
    temp_s3 = strlen(arg0);
    var_s0 = 0;
    while (1) {
        var_s1 += 1;
        if (strncmp((char *)arg0, (const char *)(D_0039D93C + var_s0), temp_s3) == 0) {
            return *(s32 *)(D_0039D93C + var_s0 - 4);
        }
        var_s0 = var_s1 * 0x10;
        if (var_s1 >= 0x20U) {
            return 0;
        }
    }
}
