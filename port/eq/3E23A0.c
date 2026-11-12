#include "m2c_macros.h"

void func_29BD28(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_004279C8 __attribute__((section(".data")));

void func_003E23A0(s32 arg0) {
    func_29BD28(arg0);
    func_26E908((u8 *)D_004279C8 + 0x10);
    func_28BB60(M2C_FIELD(D_004279C8, void **, 4));
    func_28BB60(D_004279C8);
}
