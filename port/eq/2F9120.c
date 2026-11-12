#include "common.h"

extern s8 *D_0039D6EC __attribute__((section(".data")));
extern s32 D_0039D6F0 __attribute__((section(".data")));

s8 *func_002F9120(void) {
    s32 var_a1;
    s32 count;
    s8 *var_a0;
    s8 *var_v0;

    var_a1 = 0;
    count = D_0039D6F0;
    var_a0 = D_0039D6EC;
    if (count > 0) {
        do {
            var_v0 = var_a0;
            var_a0 += 0x10;
            if (*var_v0 == 0) {
                return var_v0;
            }
            var_a1 += 1;
        } while (var_a1 < count);
    }
    return NULL;
}
