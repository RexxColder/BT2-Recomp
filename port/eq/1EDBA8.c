#include "common.h"

void func_0025E190(s32 arg0, s32 arg1, s32 arg2);

extern u8 *D_00387A40;

void func_001EDBA8(s32 arg0) {
    s32 temp_a2;

    temp_a2 = arg0 * 0x1520;
    func_0025E190((s32) (*(u8 **) ((u8 *) D_00387A40 + 8) + temp_a2), 0, temp_a2);
}
