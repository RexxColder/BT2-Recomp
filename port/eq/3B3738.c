#include "m2c_macros.h"

void func_24C030(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_00421380 __attribute__((section(".data")));

void func_003B3738(s32 arg0) {
    s32 i;

    func_24C030(arg0);
    for (i = 0; i < 3; i++) {
        func_26E908((u8 *)D_00421380 + (0x28 * i) + 0x10);
    }
    func_28BB60(M2C_FIELD(D_00421380, void **, 0x4));
    func_28BB60(D_00421380);
}
