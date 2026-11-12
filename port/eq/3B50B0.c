#include "m2c_macros.h"

void func_2B88C0(s32, s32);

void func_003B50B0(void *arg0, s32 arg1) {
    s32 temp_v1;

    if (arg0 != NULL) {
        temp_v1 = (arg1 > 0) ? 0 : arg1;
        func_2B88C0(M2C_FIELD(arg0, s32 *, 0xC0), (temp_v1 >= -0x3C0) ? temp_v1 : -0x3C0);
    }
}
