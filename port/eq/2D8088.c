#include "common.h"

s32 func_002D80D8(void);
extern s32 D_003475D4 __attribute__((section(".data")));
extern s32 D_00399D64 __attribute__((section(".data")));

void func_002D8088(void) {
    if (D_003475D4 <= 0) {
        D_00399D64 = func_002D80D8();
        D_003475D4 = D_003475D4 + 1;
    }
}
