#include "common.h"

void func_002E2668(s32 arg0) {
    s32 temp_v0;

    if (*(s32 *)(arg0 + 0x48) != 1) {
        temp_v0 = *(s32 *)(arg0 + 0x118);
        if ((temp_v0 == 1) || (temp_v0 == 2)) {
            *(s32 *)(arg0 + 0x38) = 1;
            return;
        }
        if (*(s32 *)(arg0 + 0x134) == 1) {
            *(s32 *)(arg0 + 0x38) = 3;
            return;
        }
        *(s32 *)(arg0 + 0x38) = 2;
        return;
    }
    *(s32 *)(arg0 + 0x38) = 1;
}
