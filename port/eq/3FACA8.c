#include "m2c_macros.h"

void func_26E908(void *);
void func_28BB60(void *);
extern void *D_0042A584 __attribute__((section(".data")));

void func_003FACA8(void) {
    s32 i;
    s32 off;

    i = 1;
    off = 0;
    do {
        i -= 1;
        func_26E908((u8 *)D_0042A584 + off + 0x14);
        off += 0x28;
    } while (i >= 0);
    func_28BB60(M2C_FIELD(D_0042A584, void **, 0x10));
    func_28BB60(M2C_FIELD(D_0042A584, void **, 4));
    func_28BB60(D_0042A584);
}
