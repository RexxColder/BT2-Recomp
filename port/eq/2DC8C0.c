#include "common.h"

s32 func_002DC938(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002DA7D0(void);
void func_002DC670(void);
extern u8 D_0037AF30[] __attribute__((section(".data")));
extern u8 D_0037AF80[] __attribute__((section(".data")));
extern s32 D_00399D94 __attribute__((section(".data")));

s32 func_002DC8C0(s32 arg0, s32 arg1) {
    s32 v;

    D_00399D94 = (s32)D_0037AF30;
    if (D_0037AF80[0] != 4) {
        for (;;) {
            ((void (*)(void))(s32)-1)();
        }
    }
    v = func_002DC938(arg0, arg1, 4, D_0037AF80[0]);
    if (v == 0) {
        func_002DA7D0();
        func_002DC670();
        v = 0;
    }
    return v;
}
