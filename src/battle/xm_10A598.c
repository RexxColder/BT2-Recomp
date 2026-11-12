#include "m2c_macros.h"

void func_00101700(s32);
void func_00267550(s32, s32, s32);
extern s32 *D_00387A40;

// Starts two jobs with func_00267550 on the block at *D_00387A40 (the second 0x18580 bytes further in); returns 1.
s32 func_0010A598(void) {
    func_00101700(0);
    func_00101700(1);
    func_00267550(*D_00387A40, 0, 0);
    func_00267550(*D_00387A40 + 0x18580, 0, 0);
    return 1;
}
