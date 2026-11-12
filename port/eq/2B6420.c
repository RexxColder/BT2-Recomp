#include "common.h"

u8 *func_002B61E0(void);
s32 func_002BD180(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_002B6420(u8 *arg0) {
    u8 *temp_a1;
    u8 *temp_v0;

    temp_v0 = func_002B61E0();
    memset(temp_v0, 0, 0x1890);
    func_002BD180(0);
    *(s32 *)(temp_v0 + 0x5C) = 0;
    temp_a1 = temp_v0 + 4;
    if (arg0 != NULL) {
        *(s32 *)(temp_a1 + 4) = *(s32 *)(arg0 + 4);
        *(s32 *)(temp_a1 + 0xC) = *(s32 *)(arg0 + 0xC);
        *(f32 *)(temp_v0 + 4) = *(f32 *)(arg0 + 0);
        *(s32 *)(temp_a1 + 8) = *(s32 *)(arg0 + 8);
    } else {
        *(s32 *)(temp_a1 + 0xC) = 0;
        *(f32 *)(temp_v0 + 4) = 59.94f;
        *(s32 *)(temp_a1 + 8) = 1;
        *(s32 *)(temp_a1 + 4) = 1;
    }
    *(s32 *)(temp_v0 + 0x188C) = 0;
    *(s32 *)(temp_v0 + 0x38) = 1;
    *(s32 *)(temp_v0 + 0x3C) = 0;
}
