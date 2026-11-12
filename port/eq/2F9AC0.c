#include "m2c_macros.h"

extern u8 D_0039D7F8[] __attribute__((section(".data")));

void *func_002F9AC0(void) {
    s32 k;

    for (k = 0; k < 0x28; k++) {
        if (*(s32 *)(D_0039D7F8 + k * 8 + 4) == 0) {
            return D_0039D7F8 + k * 8;
        }
    }
    return NULL;
}
