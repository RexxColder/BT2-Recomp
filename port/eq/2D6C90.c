#include "m2c_macros.h"

extern u8 D_00346EA8 __attribute__((section(".data")));

void func_002D6C90(s32 unused0, s32 unused1, s32 arg2) {
    u8 *blk = &D_00346EA8;
    void (*fn)(s32, s32, s32);

    *(s32 *)(blk + 8) = *(s32 *)(blk + 8) + 1;
    fn = *(void (**)(s32, s32, s32))blk;
    if (fn != NULL) {
        fn(*(s32 *)(blk + 4), arg2, (s32)fn);
    }
}
