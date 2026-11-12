#include "common.h"

void func_002DE020(s32 arg0);

s32 func_002CA358(void *arg0) {
    s32 temp_a0;

    temp_a0 = *(s32 *)(*(u8 **)((u8 *)arg0 + 0x1FC0));
    if (temp_a0 != 0) {
        func_002DE020(temp_a0);
    }
    return 0;
}
