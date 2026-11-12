#include "common.h"

void func_001AE5C8(u8 *arg0) {
    u8 *obj;

    if (arg0 != 0) {
        obj = *(u8 **)(arg0 + 0x38);
        obj[0x162] = 0;
        obj[0x5D] = 0;
        arg0[1] = 3;
    }
}
