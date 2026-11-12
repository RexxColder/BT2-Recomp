#include "m2c_macros.h"

void func_003B44B8(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_0042BB80 __attribute__((section(".data")));

void func_004197B0(s32 arg0) {
    s32 i;

    func_003B44B8(arg0);
    for (i = 0; i < 2; i++) {
        func_26E908((u8 *)D_0042BB80 + (0x28 * i) + 0x8);
    }
    func_28BB60(M2C_FIELD(D_0042BB80, void **, 0x4));
    func_28BB60(D_0042BB80);
}
