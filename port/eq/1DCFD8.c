#include "common.h"

extern s32 D_003878D0;

s32 func_001DCFD8(s32 arg0, s32 arg1) {
    s32 var_a2;
    s32 var_v1;

    var_a2 = 0;
    var_v1 = D_003878D0 + 0x128;
    for (;;) {
        if (*(s32 *)(var_v1 + 8) & 1) {
            var_a2 += 1;
            var_v1 += 0x14;
            if (var_a2 >= 3) {
                return 0;
            }
            continue;
        }
        *(s32 *)(var_v1 + 0) = arg0;
        *(s32 *)(var_v1 + 4) = arg1;
        *(s32 *)(var_v1 + 8) = 1;
        *(s32 *)(var_v1 + 0xC) = 0;
        *(s32 *)(var_v1 + 0x10) = 0;
        return var_v1;
    }
}
