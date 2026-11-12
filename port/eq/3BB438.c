#include "m2c_macros.h"

void func_29BD28(s32);
void func_28BB60(void *);
extern void *D_00421C00 __attribute__((section(".data")));

void func_003BB438(s32 arg0) {
    func_29BD28(arg0);
    func_28BB60(M2C_FIELD(D_00421C00, void **, 4));
    func_28BB60(M2C_FIELD(D_00421C00, void **, 0));
    func_28BB60(D_00421C00);
}
