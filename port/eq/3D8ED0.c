#include "m2c_macros.h"

void func_26E908(void *);
void func_250D90(void);
void func_28BB60(void *);
extern void *D_004263E8 __attribute__((section(".data")));

void func_003D8ED0(void) {
    s32 i;
    s32 off;

    i = 1;
    off = 0;
    do {
        i -= 1;
        func_26E908((u8 *)D_004263E8 + off + 0x1C);
        off += 0x28;
    } while (i >= 0);
    func_250D90();
    func_28BB60(M2C_FIELD(D_004263E8, void **, 4));
    func_28BB60(D_004263E8);
}
