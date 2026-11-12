#include "common.h"

s32 func_002D6960(s32 arg0);
void func_002D6970(void);
void func_002D71B8(void);
void func_002D71E8(void);
void func_002E0CC0(void);
extern s32 D_00346E98 __attribute__((section(".data")));
extern s32 D_00346E9C __attribute__((section(".data")));
extern s32 D_00399D60 __attribute__((section(".data")));

void func_002D68F0(s32 arg0) {
    if (D_00346E98 <= 0) {
        D_00399D60 = func_002D6960(arg0);
        func_002D6970();
        func_002D71B8();
        func_002D71E8();
        func_002E0CC0();
        D_00346E9C = 0;
        D_00346E98 += 1;
    }
}
