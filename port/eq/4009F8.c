#include "m2c_macros.h"

void func_26E908(void *);
void func_28BB60(void *);
extern void *D_0042A590 __attribute__((section(".data")));

void func_004009F8(void) {
    s32 i;
    s32 off;

    i = 5;
    off = 0;
    do {
        i -= 1;
        func_26E908((u8 *)D_0042A590 + off + 0x2C);
        off += 0x28;
    } while (i >= 0);
    func_28BB60(M2C_FIELD(D_0042A590, void **, 0x18));
    func_28BB60(M2C_FIELD(D_0042A590, void **, 0x1C));
    func_28BB60(M2C_FIELD(D_0042A590, void **, 0x20));
    func_28BB60(M2C_FIELD(D_0042A590, void **, 8));
    func_28BB60(M2C_FIELD(D_0042A590, void **, 0xC));
    func_28BB60(M2C_FIELD(D_0042A590, void **, 0x10));
    func_28BB60(M2C_FIELD(D_0042A590, void **, 0x14));
    func_28BB60(M2C_FIELD(D_0042A590, void **, 4));
    func_28BB60(D_0042A590);
}
