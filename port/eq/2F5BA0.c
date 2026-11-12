#include "common.h"

void func_002EA050(s32 arg0);
extern u8 D_0037CBC8[] __attribute__((section(".data")));

typedef s32 (*VFunc2)(s32, s32);

s32 func_002F5BA0(u8 *arg0) {
    u8 *temp_v1;
    s32 r;

    if (arg0 == NULL) {
        func_002EA050((s32)D_0037CBC8);
        return -1;
    }
    temp_v1 = *(u8 **)(arg0 + 0x14);
    if (temp_v1 != NULL) {
        u8 *vt = *(u8 **)temp_v1;
        r = ((VFunc2)(*(s32 *)(vt + 0x24)))((s32)temp_v1, 1);
        return (r < (s32)(*(s16 *)(arg0 + 0x3E)) * 2048) ? 0 : 1;
    }
    return 0;
}
