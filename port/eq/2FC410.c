#include "common.h"

s32 func_002FC330(s32 arg0);
s32 func_002FC370(s32 arg0);
extern s8 D_00355339 __attribute__((section(".data")));

s32 func_002FC410(void) {
    if (D_00355339 == 1) {
        return func_002FC330(D_00355339) * 2;
    }
    if (D_00355339 == 2) {
        return func_002FC370(D_00355339);
    }
    return 0;
}
