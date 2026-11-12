#include "common.h"

extern s32 (*D_00347BD8)(s32, s32) __attribute__((section(".data")));
extern s32 D_00347BDC __attribute__((section(".data")));

s32 func_002E7038(s32 arg0) {
    if (D_00347BD8 != NULL) {
        D_00347BD8(D_00347BDC, arg0);
    }
    return 0;
}
