#include "common.h"

u8 *func_002B61E0(void);

void func_002BCE58(s32 arg0, s32 arg1) {
    u8 *p = func_002B61E0();

    *(s32 *)(p + 0x54) = arg1;
    *(s32 *)(p + 0x50) = arg0;
}
