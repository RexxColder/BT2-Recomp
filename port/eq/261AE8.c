#include "common.h"

void func_00266900(s32 arg0, f32 farg0);

extern u8 *D_00387A40;

/* f12 (farg0) passes through to the tail-called func_00266900, which stores it at +0xB98; a1 is not read there. */
void func_00261AE8(s32 arg0, f32 farg0) {
    s32 temp_a1;

    temp_a1 = (arg0 & 0xFFFF) * 0x1520;
    func_00266900((s32) (*(u8 **) ((u8 *) D_00387A40 + 8) + temp_a1), farg0);
}
