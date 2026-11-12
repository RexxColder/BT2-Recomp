#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);

void func_00168D58(s32 arg0) {
    s32 *p = *(s32 **)(*(u8 **)(arg0 + 0x38) + 0x120);

    BtlScene_IsCharStopped(*p);
}
