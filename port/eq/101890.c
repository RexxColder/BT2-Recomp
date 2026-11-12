#include "common.h"

void func_002F52A8(s32 arg0, s32 arg1);
s32 func_002F5358(s32 arg0);

extern s32 D_00387F08;

void func_00101890(void) {
    func_002F52A8(D_00387F08, func_002F5358(D_00387F08) - 0x7D);
}
