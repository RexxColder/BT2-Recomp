#include "m2c_macros.h"

void func_24C030(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_00428F4C __attribute__((section(".data")));

void func_003ED9C0(s32 arg0) {
    s32 i;
    s32 off;

    func_24C030(arg0);
    i = 3;
    off = 0;
    do {
        i -= 1;
        func_26E908((u8 *)D_00428F4C + off + 0x28);
        off += 0x28;
    } while (i >= 0);
    func_28BB60(M2C_FIELD(D_00428F4C, void **, 0x1C));
    func_28BB60(M2C_FIELD(D_00428F4C, void **, 0x20));
    func_28BB60(M2C_FIELD(D_00428F4C, void **, 4));
    func_28BB60(D_00428F4C);
}
