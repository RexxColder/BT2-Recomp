#include "m2c_macros.h"

void func_24C030(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_004263EC __attribute__((section(".data")));

void func_003DBBC0(s32 arg0) {
    func_24C030(arg0);
    func_26E908((u8 *)D_004263EC + 0x10);
    func_28BB60(M2C_FIELD(D_004263EC, void **, 4));
    func_28BB60(D_004263EC);
}
