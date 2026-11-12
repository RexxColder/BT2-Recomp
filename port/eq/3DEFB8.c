#include "m2c_macros.h"

void func_26E908(void *);
void func_28BB60(void *);
extern void *D_00427330 __attribute__((section(".data")));

void func_003DEFB8(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_26E908((u8 *)D_00427330 + (0x28 * i) + 0x14);
    }
    func_28BB60(M2C_FIELD(D_00427330, void **, 0x4));
    func_28BB60(D_00427330);
}
