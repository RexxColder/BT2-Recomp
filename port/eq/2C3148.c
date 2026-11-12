#include "common.h"

extern u8 D_00346C28[] __attribute__((section(".data")));

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002C3210(u8 *arg0);
s32 func_002C2FF0(s32 arg0, s32 arg1);

s32 func_002C3148(u8 *arg0, u8 *arg1) {
    if (arg0 == NULL) {
        memcpy(arg1, D_00346C28 + 0x19C, 0x14);
        return 0;
    }
    if (func_002C3210(arg0) == 0) {
        memcpy(arg1, arg0 + 0x9F8, 0x14);
        return 0;
    }
    return func_002C2FF0(0, (s32)0xFF000102);
}
