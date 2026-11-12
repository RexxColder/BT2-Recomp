#include "common.h"

s32 strcmp(const char *s1, const char *s2);

s32 func_002701F0(s32 arg0, s32 arg1) {
    u32 var_s2;
    s32 var_s0;

    var_s2 = 0;
    var_s0 = *(s32 *)arg0;
    if (*(u32 *)(arg0 + 4) != 0) {
        for (;;) {
            if (strcmp((const char *)var_s0, (const char *)arg1) == 0) {
                return var_s0;
            }
            var_s2 += 1;
            var_s0 += 0xC0;
            if (var_s2 >= *(u32 *)(arg0 + 4)) {
                break;
            }
        }
    }
    return 0;
}
