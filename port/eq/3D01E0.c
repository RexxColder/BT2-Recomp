#include "m2c_macros.h"

void func_26E908(void *);
void func_28BB60(void *);
extern void *D_00423120 __attribute__((section(".data")));

void func_003D01E0(void) {
    s32 i;
    s32 off;

    i = 7;
    off = 0;
    do {
        i -= 1;
        func_26E908((u8 *)D_00423120 + off + 0x30);
        off += 0x28;
    } while (i >= 0);
    func_28BB60(M2C_FIELD(D_00423120, void **, 8));
    func_28BB60(M2C_FIELD(D_00423120, void **, 0xC));
    func_28BB60(M2C_FIELD(D_00423120, void **, 0x10));
    func_28BB60(M2C_FIELD(D_00423120, void **, 0x14));
    func_28BB60(M2C_FIELD(D_00423120, void **, 0x18));
    func_28BB60(M2C_FIELD(D_00423120, void **, 4));
    func_28BB60(M2C_FIELD(D_00423120, void **, 0));
    func_28BB60(D_00423120);
}
