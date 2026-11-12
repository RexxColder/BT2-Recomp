#include "common.h"

u8 *func_002B1DD0(s32 arg0);
extern u8 *D_00387E18;

void func_002B2188(void) {
    s32 var_s0;
    u8 *temp_s3;
    u8 *var_s1;

    var_s0 = 0;
    var_s1 = NULL;
    temp_s3 = func_002B1DD0(0);
loop_1:
    if (var_s0 < *(s32 *)(D_00387E18 + 4)) {
        if (*(s32 *)(func_002B1DD0(var_s0) + 0x10) != 3) {
            var_s0 += 1;
            goto loop_1;
        }
        var_s1 = func_002B1DD0(var_s0);
    }
    if ((var_s1 != NULL) && (((*(s32 *)(temp_s3 + 0x170)) >> *(s32 *)(var_s1 + 4)) & 1)) {
        *(u8 *)(D_00387E18 + 0xA) = 1;
    }
}
