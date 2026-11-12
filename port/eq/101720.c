#include "common.h"

s32 func_002F4590(s32 arg0);

extern s32 D_00387F00[] __attribute__((section(".data")));

s32 func_00101720(s32 arg0) {
    return func_002F4590(D_00387F00[arg0]);
}
