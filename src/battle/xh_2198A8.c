#include "m2c_macros.h"

M2C_UNK func_00211418(M2C_UNK, s32);                /* extern */

// Switch on arg1: 0x10 increments field 0x9A0 and calls func_00211418(arg0,0x2000); 0x70 increments field 0x9A8.
void func_002198A8(void *arg0, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 0x10:
        M2C_FIELD(arg0, s32 *, 0x9A0) = (s32) (M2C_FIELD(arg0, s32 *, 0x9A0) + 1);
        func_00211418(arg0, 0x2000);
        return;
    case 0x70:
        M2C_FIELD(arg0, s32 *, 0x9A8) = (s32) (M2C_FIELD(arg0, s32 *, 0x9A8) + 1);
        return;
    }
}
