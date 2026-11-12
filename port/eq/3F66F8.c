#include "m2c_macros.h"

void func_26E908(void *);
void func_28BB60(void *);
extern void *D_0042A578 __attribute__((section(".data")));

void func_003F66F8(void) {
    s32 i;
    s32 off;

    i = 3;
    off = 0;
    do {
        i -= 1;
        func_26E908((u8 *)D_0042A578 + off + 0x10);
        off += 0x28;
    } while (i >= 0);
    func_28BB60(M2C_FIELD(D_0042A578, void **, 8));
    func_28BB60(M2C_FIELD(D_0042A578, void **, 4));
    func_28BB60(D_0042A578);
}
