#include "common.h"

s32 *func_002D72A0(void);
void func_002D72F0(s32 *arg0);
extern s32 D_00347368 __attribute__((section(".data")));

s32 *func_002D7248(void) {
    s32 *temp_v0;

    temp_v0 = func_002D72A0();
    if (temp_v0 != NULL) {
        func_002D72F0(temp_v0);
        D_00347368 += 1;
        *temp_v0 = 1;
    }
    return temp_v0;
}
