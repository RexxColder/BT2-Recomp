#include "common.h"

s32 strncmp(char *arg0, const char *arg1, u32 arg2);
extern s32 D_0039D6EC __attribute__((section(".data")));
extern s32 D_0039D6F0 __attribute__((section(".data")));

s32 func_002F9170(s8 *arg0) {
    s32 var_s0;
    s32 var_s1;

    if (*arg0 == 0) {
        return 0;
    }
    var_s1 = 0;
    var_s0 = D_0039D6EC;
    if (D_0039D6F0 > 0) {
        do {
            var_s1 += 1;
            if (strncmp((char *)var_s0, (const char *)arg0, 0xC) == 0) {
                return var_s0;
            }
            var_s0 += 0x10;
        } while (var_s1 < D_0039D6F0);
    }
    return 0;
}
