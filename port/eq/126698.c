#include "common.h"

extern u8 *D_003876A0;
extern u8 *gBtlScene;

s32 func_00126698(void) {
    s32 r = 1;

    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        r = *(u8 *)(gBtlScene + 0x24);
    }
    return r;
}
