#include "common.h"

s32 EftPtcl3_IsAlive(s32 arg0);

s32 func_001A5E48(s32 *arg0) {
    s32 *var_s0;
    s32 var_s2;
    s32 var_s3;
    s32 var_v0;
    u8 *temp_v1;

    var_v0 = 0;
    var_s3 = 0;
    if (*(s32 *)((u8 *)arg0 + 0x10) != 0) {
        if (*(s32 *)((u8 *)arg0 + 0x14) != 0) {
            temp_v1 = *(u8 **)((u8 *)arg0 + 0xC);
            if ((temp_v1 != NULL) && (*(s32 *)(temp_v1 + 0x100) != 0)) {
                var_s2 = 0;
                if (*(s32 *)((u8 *)arg0 + 0x68) > 0) {
                    var_s0 = arg0;
                    do {
                        if (EftPtcl3_IsAlive(*var_s0) == 0) {
                            *var_s0 = 0;
                        } else {
                            var_s3 = 1;
                        }
                        var_s2 += 1;
                        var_s0 += 1;
                    } while (var_s2 < *(s32 *)((u8 *)arg0 + 0x68));
                }
                var_v0 = var_s3;
            }
        }
    }
    return var_v0;
}
