#include "common.h"

extern u8 **D_00387A40;
extern void func_00101700(s32 a0);
extern void func_00267550(u8 *p, s32 a1, s32 a2);

/* 0x0010A598: init two things, run func_00267550 on the base pointer and base + 0x18580; returns 1. */
s32 func_0010A598(void) {
    func_00101700(0);
    func_00101700(1);
    func_00267550(*D_00387A40, 0, 0);
    func_00267550(*D_00387A40 + 0x18580, 0, 0);
    return 1;
}
