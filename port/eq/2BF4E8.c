#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);

void func_002BF4E8(u8 *arg0, s32 arg1) {
    void (*temp_v0)(u8 *, s32);
    u8 *temp_p;

    if (func_002D07B0((s32)arg0, 6) != 0) {
        temp_p = *(u8 **)(arg0 + 0x2114);
        temp_v0 = *(void (**)(u8 *, s32))(temp_p + 0x14);
        if (temp_v0 != NULL) {
            temp_v0(arg0, arg1);
        }
    }
}
