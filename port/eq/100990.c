#include "common.h"

extern s32 D_00387F20[];
s32 func_002EAFA8(s32 arg0);
void func_002EF218();

s32 func_00100990(s32 arg0) {
    while (func_002EAFA8(D_00387F20[arg0]) != 3) {
        func_002EF218(arg0);
    }
    return 1;
}
