#include "m2c_macros.h"

void func_24C030(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_0042FD74 __attribute__((section(".data")));

void func_0041DB28(s32 arg0) {
    s32 i;
    s32 off;

    func_24C030(arg0);
    i = 1;
    off = 0;
    do {
        i -= 1;
        func_26E908((u8 *)D_0042FD74 + off + 0x1C);
        off += 0x28;
    } while (i >= 0);
    func_28BB60(M2C_FIELD(D_0042FD74, void **, 8));
    func_28BB60(M2C_FIELD(D_0042FD74, void **, 0xC));
    func_28BB60(M2C_FIELD(D_0042FD74, void **, 4));
    func_28BB60(D_0042FD74);
}
