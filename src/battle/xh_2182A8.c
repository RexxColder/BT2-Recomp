#include "m2c_macros.h"

s32 BtlPad_Test4C();                 /* extern */

// Sets field 0x9C0 to 3, 2, 1 or 0 for each BtlPad_Test4C(arg, 3/2/1/0) that passes; the last passing test wins.
void func_002182A8(void *arg0) {
    if (BtlPad_Test4C(arg0, 3) != 0) {
        M2C_FIELD(arg0, s32 *, 0x9C0) = 3;
    }
    if (BtlPad_Test4C(arg0, 2) != 0) {
        M2C_FIELD(arg0, s32 *, 0x9C0) = 2;
    }
    if (BtlPad_Test4C(arg0, 1) != 0) {
        M2C_FIELD(arg0, s32 *, 0x9C0) = 1;
    }
    if (BtlPad_Test4C(arg0, 0) != 0) {
        M2C_FIELD(arg0, s32 *, 0x9C0) = 0;
    }
}
