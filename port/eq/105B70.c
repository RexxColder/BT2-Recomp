#include "common.h"

u8 *func_00105A88(void);

void func_00105B70(s32 arg0, s32 arg1) {
    u8 *p = func_00105A88();

    *(s32 *)(p + 4) = arg1;
    *(s32 *)(p + 0) = arg0;
}
