#include "m2c_macros.h"

s32 func_105200(s32);
void func_26E908(void *);
void func_28BB60(void *);
extern void *D_0042732C __attribute__((section(".data")));

void func_003DD100(s32 arg0) {
    func_105200(arg0);
    func_26E908((u8 *)D_0042732C + 0x2C);
    func_28BB60(M2C_FIELD(D_0042732C, void **, 0x8));
    func_28BB60(M2C_FIELD(D_0042732C, void **, 0xC));
    func_28BB60(M2C_FIELD(D_0042732C, void **, 0x4));
    func_28BB60(D_0042732C);
}
