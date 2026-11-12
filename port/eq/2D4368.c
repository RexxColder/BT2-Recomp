#include "common.h"

s32 func_002D4348(s32 *arg0);
void func_002D4588(s32 arg0, s32 arg1);
void func_002D4548(s32 *arg0, s32 arg1, s32 arg2);
extern s32 D_00399D48 __attribute__((section(".data")));
extern s32 D_00399D50 __attribute__((section(".data")));
extern s32 D_00399D5C __attribute__((section(".data")));

void func_002D4368(s32 arg0, s32 arg1) {
    if (D_00399D5C <= 0) {
        D_00399D5C += 1;
        D_00399D48 = func_002D4348(&D_00399D5C);
        func_002D4588(arg0, arg1);
        func_002D4548(&D_00399D50, arg0, arg1);
    }
}
