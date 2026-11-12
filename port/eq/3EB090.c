#include "m2c_macros.h"

void func_26E908(void *);
void func_28BB60(void *);
extern void *D_00428F48 __attribute__((section(".data")));

void func_003EB090(void) {
    s32 i;
    s32 off;

    i = 4;
    off = 0;
    do {
        i -= 1;
        func_26E908((u8 *)D_00428F48 + off + 0x28);
        off += 0x28;
    } while (i >= 0);
    func_28BB60(M2C_FIELD(D_00428F48, void **, 0x20));
    func_28BB60(M2C_FIELD(D_00428F48, void **, 0x24));
    func_28BB60(M2C_FIELD(D_00428F48, void **, 4));
    func_28BB60(D_00428F48);
}
