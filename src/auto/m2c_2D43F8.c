#include "m2c_macros.h"

M2C_UNK func_002D4538(M2C_UNK *);                   /* extern */
extern M2C_UNK D_00399D50 __attribute__((section(".data")));
extern s32 D_00399D5C __attribute__((section(".data")));

void func_002D43F8(void) {
    s32 temp_v0;

    temp_v0 = D_00399D5C - 1;
    D_00399D5C = temp_v0;
    if (temp_v0 <= 0) {
        func_002D4538(&D_00399D50);
    }
}
