#include "m2c_macros.h"

extern u8 *D_003878C8;

void *func_001CDB00(void) {
    s32 i = 0;
    u8 *p = D_003878C8 + 0x120;

    while (1) {
        if (*(u16 *)(p + 4) == 0) {
            return p;
        }
        p += 0x10;
        i++;
        if (i >= 0xF) {
            return NULL;
        }
    }
}
