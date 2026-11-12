#include "common.h"

extern s32 D_003877B4 __attribute__((section(".data")));

s32 func_00189F50(void) {
    s32 var_a0;

    if (*(s32 *) (D_003877B4 + 0x7AF0) >= 0x96) {
        *(s32 *) (D_003877B4 + 0x7AF0) = 0;
    }
    var_a0 = D_003877B4 + (*(s32 *) (D_003877B4 + 0x7AF0) * 0xD0) + 0x110;
    for (;;) {
        *(s32 *) (D_003877B4 + 0x7AF0) = *(s32 *) (D_003877B4 + 0x7AF0) + 1;
        if (*(u16 *) (var_a0 + 0xBE) != 0) {
            var_a0 += 0xD0;
            if (*(s32 *) (D_003877B4 + 0x7AF0) >= 0x96) {
                *(s32 *) (D_003877B4 + 0x7AF0) = 0;
                return 0;
            }
            continue;
        }
        *(s32 *) (var_a0 + 0xC0) = 0;
        *(s32 *) (var_a0 + 0xC4) = 0;
        return var_a0;
    }
}
