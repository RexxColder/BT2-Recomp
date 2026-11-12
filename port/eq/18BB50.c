#include "common.h"

extern s32 D_003877B4;

void func_0018BB50(u8 *arg0, u8 *arg1) {
    s64 sp0;
    s64 sp8;
    u8 *temp_a0;

    sp8 = *(s64 *)(arg1 + 8);
    sp0 = *(s64 *)(arg1 + 0);
    if ((D_003877B4 != 0) && (arg0 != NULL)) {
        temp_a0 = *(u8 **)(arg0 + 0x38);
        if ((temp_a0 != NULL) && (*(s32 *)(temp_a0 + 0x1D8) & 2)) {
            /* the float at sp+0xC is the high word of sp8: forced to 1.0f when it is not 1.0f */
            if (((u32)((u64)sp8 >> 32)) != 0x3F800000u) {
                sp8 = (sp8 & 0xFFFFFFFFLL) | ((s64)0x3F800000 << 32);
            }
            *(s64 *)(temp_a0 + 0x40) = sp0;
            *(s64 *)(temp_a0 + 0x48) = sp8;
        }
    }
}
