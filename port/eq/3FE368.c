#include "m2c_macros.h"

void func_29BD28(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_0042A58C __attribute__((section(".data")));

void func_003FE368(s32 arg0) {
    func_29BD28(arg0);
    func_26E908((u8 *)D_0042A58C + 0xC);
    func_28BB60(M2C_FIELD(D_0042A58C, void **, 4));
    func_28BB60(D_0042A58C);
}
