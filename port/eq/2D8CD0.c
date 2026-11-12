#include "common.h"

void func_002D8D40(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

extern u8 *D_00399D90 __attribute__((section(".data")));
extern u8 D_0037AEA0[] __attribute__((section(".data")));

void func_002D8CD0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_00399D90 = D_0037AEA0;
    func_002D8D40(arg0, arg1, arg2, arg3);
}
