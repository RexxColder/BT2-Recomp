#include "common.h"

s32 memcpy(s32 arg0, s32 arg1, s32 arg2);
s32 strlen(s32 arg0);
extern s8 D_0039DB38 __attribute__((section(".data")));

void func_002F9C80(s32 arg0) {
    s32 temp_a2;

    temp_a2 = strlen((s32)&D_0039DB38) + 1;
    if (D_0039DB38 == 0) {
        *(s8 *)arg0 = 0;
        return;
    }
    memcpy(arg0, (s32)&D_0039DB38, temp_a2);
}
