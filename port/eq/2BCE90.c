#include "common.h"

s32 func_002B61E0(s32 arg0);

void func_002BCE90(s32 arg0) {
    void (*temp_v1)(s32);
    s32 temp_v0;

    temp_v0 = func_002B61E0(arg0);
    temp_v1 = *(void (**)(s32))((u8 *)temp_v0 + 0x50);
    if (temp_v1 != NULL) {
        temp_v1(*(s32 *)((u8 *)temp_v0 + 0x54));
    }
}
