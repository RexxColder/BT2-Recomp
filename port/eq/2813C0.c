#include "common.h"

extern u8 *D_00387AFC;

void func_002813C0(s8 arg0) {
    if (arg0 == 0) {
        *(u8 *) ((u8 *) D_00387AFC + 0x3CC9) = 1;
    }
    if (arg0 == 1) {
        *(s8 *) ((u8 *) D_00387AFC + 0x3CC8) = arg0;
    }
}
