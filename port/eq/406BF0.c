#include "m2c_macros.h"

void func_29BD28(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_0042BB74 __attribute__((section(".data")));

void func_00406BF0(s32 arg0) {
    s32 i;
    s32 off;

    func_29BD28(arg0);
    i = 5;
    off = 0;
    do {
        i -= 1;
        func_26E908((u8 *)D_0042BB74 + off + 0x28);
        off += 0x28;
    } while (i >= 0);
    func_28BB60(M2C_FIELD(D_0042BB74, void **, 0x18));
    func_28BB60(M2C_FIELD(D_0042BB74, void **, 8));
    func_28BB60(M2C_FIELD(D_0042BB74, void **, 0xC));
    func_28BB60(M2C_FIELD(D_0042BB74, void **, 0x10));
    func_28BB60(M2C_FIELD(D_0042BB74, void **, 0x14));
    func_28BB60(M2C_FIELD(D_0042BB74, void **, 4));
    func_28BB60(D_0042BB74);
}
