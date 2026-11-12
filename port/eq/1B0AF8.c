#include "common.h"

extern u8 *D_00387858;

s32 func_001B0AF8(s32 arg0) {
    s32 *p = *(s32 **)(D_00387858 + arg0 * 4 + 0xCC);

    if (p != NULL) {
        return *p;
    }
    return 0;
}
