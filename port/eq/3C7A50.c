#include "m2c_macros.h"

void func_29BD28(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_00423114 __attribute__((section(".data")));

void func_003C7A50(s32 arg0) {
    s32 i;
    s32 off;

    func_29BD28(arg0);
    i = 3;
    off = 0;
    do {
        i -= 1;
        func_26E908((u8 *)D_00423114 + off + 0x20);
        off += 0x28;
    } while (i >= 0);
    func_28BB60(M2C_FIELD(D_00423114, void **, 0x10));
    func_28BB60(M2C_FIELD(D_00423114, void **, 8));
    func_28BB60(M2C_FIELD(D_00423114, void **, 0xC));
    func_28BB60(M2C_FIELD(D_00423114, void **, 4));
    func_28BB60(D_00423114);
}
