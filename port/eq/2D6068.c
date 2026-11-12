#include "common.h"

void func_002D6068(u8 *arg0) {
    void (*temp_v0)(s32);

    temp_v0 = *(void (**)(s32))(arg0 + 0x70);
    if (temp_v0 != NULL) {
        temp_v0(*(s32 *)(arg0 + 0x38));
    }
}
