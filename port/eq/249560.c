#include "m2c_macros.h"

s32 rand(void);

void func_00249560(s32 *arg0) {
    s32 temp_v0;
    s32 t;

    temp_v0 = rand();
    t = (temp_v0 < 0) ? (temp_v0 + 0x1F) : temp_v0;
    *arg0 = temp_v0 - ((t >> 5) << 5);
}
