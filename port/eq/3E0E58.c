#include "m2c_macros.h"

void func_26E908(void *);
void func_28BB60(void *);
extern void *D_00427338 __attribute__((section(".data")));

void func_003E0E58(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_26E908((u8 *)D_00427338 + (0x28 * i) + 0x8);
    }
    func_28BB60(M2C_FIELD(D_00427338, void **, 0x4));
    func_28BB60(D_00427338);
}
