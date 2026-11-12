#include "m2c_macros.h"

void func_24C030(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_0042A580 __attribute__((section(".data")));

void func_003F9B10(s32 arg0) {
    s32 i;

    func_24C030(arg0);
    for (i = 0; i < 3; i++) {
        func_26E908((u8 *)D_0042A580 + (0x28 * i) + 0x14);
    }
    func_28BB60(M2C_FIELD(D_0042A580, void **, 0x4));
    func_28BB60(D_0042A580);
}
