#include "common.h"

extern u8 D_00387E80[];

void func_00113510(u8 *arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        arg0[i] = D_00387E80[i];
    }
}
