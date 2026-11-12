#include "common.h"

void func_002F9300(s32 arg0);
extern u8 D_0037DA18[] __attribute__((section(".data")));
extern u8 D_0039D938[] __attribute__((section(".data")));
extern u8 D_0039D93C[] __attribute__((section(".data")));

s32 func_002FAB68(s32 arg0) {
    s32 temp_a0;
    s32 var_a1;
    s32 var_a2;

    if (arg0 == 0) {
        func_002F9300((s32) D_0037DA18);
        return 0;
    }
    temp_a0 = *(s32 *) arg0;
    var_a1 = 0;
    if (*(s32 *) D_0039D938 != temp_a0) {
        var_a2 = 1;
        for (;;) {
            var_a1 = var_a2 * 0x10;
            if (var_a2 >= 0x20) {
                break;
            }
            if (*(s32 *) ((s32) D_0039D938 + var_a1) == temp_a0) {
                break;
            }
            var_a2 += 1;
        }
    }
    return (s32) D_0039D93C + var_a1;
}
