#include "common.h"

s32 *func_002E0D78(void);
void func_002E0DC8(s32 *arg0);
extern s32 D_00347A30 __attribute__((section(".data")));

s32 *func_002E0D20(void) {
    s32 *temp_v0;

    temp_v0 = func_002E0D78();
    if (temp_v0 != NULL) {
        func_002E0DC8(temp_v0);
        D_00347A30 += 1;
        *temp_v0 = 1;
    }
    return temp_v0;
}
