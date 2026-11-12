#include "m2c_macros.h"

void *memset(void *, int, unsigned int);

void func_0026C1B0(s32 *arg0) {
    s32 temp_s0;

    temp_s0 = *arg0;
    memset(arg0, 0, 0x44);
    *arg0 = temp_s0;
}
