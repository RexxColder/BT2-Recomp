#include "common.h"

void func_002BDC28(void **arg0, s32 arg1, s32 arg2) {
    void (*fn)(void *, s32, s32, s32);

    fn = *(void (**)(void *, s32, s32, s32)) ((u8 *) *arg0 + 0x18);
    fn(arg0, 0, arg1, arg2);
}
