#include "m2c_macros.h"

void func_26E908(void *);
void func_28BB60(void *);
extern void *D_0042FD70 __attribute__((section(".data")));

void func_0041C460(void) {
    func_26E908((u8 *)D_0042FD70 + 0xC);
    func_28BB60(M2C_FIELD(D_0042FD70, void **, 4));
    func_28BB60(D_0042FD70);
}
