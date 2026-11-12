#include "common.h"

extern u8 *D_003876A0;
void func_00276FD0(f32 farg0);
void func_001014E8(s32 arg0);

void func_00277890(void) {
    s64 x = *(s64 *)(D_003876A0 + 0x4D8);

    if ((x & 3) != 0) {
        func_00276FD0(0.25f);
        return;
    }
    if ((x & 8) != 0) {
        func_001014E8(-0x3C0);
    }
}
