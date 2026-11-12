#include "common.h"

extern u8 *D_00387A40;
void func_00206A98(s32 arg0, s32 arg1);

void func_00206F90(s32 arg0) {
    s32 v1 = *(s32 *)(arg0 + 0x142C);

    if (v1 < 0) {
        return;
    }
    if (v1 < *(s32 *)(D_00387A40 + 0xC)) {
        u8 *p = (u8 *)*(s32 *)(D_00387A40 + 0x8) + v1 * 0x1520;
        func_00206A98((s32)p, arg0);
    }
}
