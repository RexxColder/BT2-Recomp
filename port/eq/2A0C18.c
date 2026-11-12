#include "common.h"

extern u8 D_00387DF0 __attribute__((section(".data")));
extern s8 D_00387DF1 __attribute__((section(".data")));

void func_002A0C18(s32 arg0) {
    if (D_00387DF0 != 0) {
        D_00387DF1 = (s8)(arg0 & 0xFF);
    }
}
