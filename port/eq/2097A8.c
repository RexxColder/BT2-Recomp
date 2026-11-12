#include "common.h"

u8 *func_00211288(s32 arg0);
void func_003126C8(void *arg0, void *arg1);
extern s32 D_00387930;

/* 0x002097A8(i, a1, a2, a3, t0): when D_00387930 is set and i < 2 (unsigned): s0 = func_00211288(i) and
 * func_003126C8 fills the four blocks at s0 + 0x180, 0x190, 0x1A0, 0x1B0 into a1, a2, a3, t0. */
void func_002097A8(s32 arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4) {
    u8 *s0;

    if (D_00387930 != 0 && (u32)arg0 < 2U) {
        s0 = func_00211288(arg0);
        func_003126C8(arg1, s0 + 0x180);
        func_003126C8(arg2, s0 + 0x190);
        func_003126C8(arg3, s0 + 0x1A0);
        func_003126C8(arg4, s0 + 0x1B0);
    }
}
