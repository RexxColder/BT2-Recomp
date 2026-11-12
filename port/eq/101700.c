#include "common.h"

void func_002F44A0(s32 arg0);

extern s32 D_00387F00[] __attribute__((section(".data")));

void func_00101700(s32 arg0) {
    func_002F44A0(D_00387F00[arg0]);
}
