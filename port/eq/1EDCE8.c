#include "common.h"

void func_00260A50(s32 arg0, s32 arg1);

extern u8 *D_00387A40;

void func_001EDCE8(s32 arg0) {
    s32 temp_a1;
    s32 base;

    temp_a1 = arg0 * 0x1520;
    base = *(s32 *)(D_00387A40 + 8);
    func_00260A50(base + temp_a1, temp_a1);
}
