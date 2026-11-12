#include "common.h"

void func_002EA588(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_00387F10[];
extern s32 D_00387F20[];
extern u8 D_0036C370[];

void func_00100950(s32 arg0) {
    D_00387F20[arg0] = 1;
    func_002EA588(1, (s32)D_0036C370, 0, D_00387F10[arg0]);
}
