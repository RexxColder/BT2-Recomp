#include "common.h"

extern s32 func_002B8280(s32 arg0);
extern s32 Rand_Range(void *range, s32 arg1);
extern void func_002BAD68(s32 arg0, s32 arg1);
extern void func_002BAF08(s32 arg0);
extern u8 D_00379BE8[] __attribute__((section(".data")));

s32 func_002BAEA0(u8 *self) {
    if (func_002B8280((s32)self) != 1) {
        return Rand_Range(D_00379BE8, 0);
    }
    func_002BAD68((s32)self, 0);
    func_002BAF08((s32)self);
    *(s32 *)(self + 0x2E8) = 4;
    return 4;
}
