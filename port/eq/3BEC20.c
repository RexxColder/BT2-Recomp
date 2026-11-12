#include "m2c_macros.h"

void func_29BD28(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_00421C94 __attribute__((section(".data")));

void func_003BEC20(s32 arg0) {
    s32 i;

    func_29BD28(arg0);
    for (i = 0; i < 2; i++) {
        func_26E908((u8 *)D_00421C94 + (0x28 * i) + 0x448);
    }
    func_28BB60(M2C_FIELD(D_00421C94, void **, 0x4));
    func_28BB60(D_00421C94);
}
