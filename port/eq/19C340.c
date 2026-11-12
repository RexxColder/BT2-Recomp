#include "common.h"

s32 func_0019C208(u8 *arg0, u8 *arg1, u8 *arg2);
extern u8 *D_003877EC;

void func_0019C340(s32 arg0) {
    s32 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *var_s0;

    var_s0 = *(u8 **)(D_003877EC + 0x238);
    if (var_s0 != NULL) {
        var_v0 = *(s32 *)(var_s0 + 4);
loop_2:
        if (var_v0 == arg0) {
            temp_v0 = *(u8 **)(var_s0 + 0);
            if (temp_v0 == NULL) {
                *(u8 **)(var_s0 + 0) = NULL;
                *(s32 *)(var_s0 + 8) = 0;
                func_0019C208(D_003877EC + 0x238, D_003877EC + 0x23C, var_s0);
                goto block_10;
            }
            temp_v1 = *(u8 **)(temp_v0 + 0x38);
            if (temp_v1 != NULL) {
                *(u16 *)(temp_v1 + 0x88) = (u16)(*(u16 *)(temp_v1 + 0x88) | 2);
                *(u8 **)(var_s0 + 0) = NULL;
                *(s32 *)(var_s0 + 8) = 0;
                func_0019C208(D_003877EC + 0x238, D_003877EC + 0x23C, var_s0);
            }
        } else {
block_10:
            var_s0 = *(u8 **)(var_s0 + 0xC);
            if (var_s0 != NULL) {
                var_v0 = *(s32 *)(var_s0 + 4);
                goto loop_2;
            }
        }
    }
}
