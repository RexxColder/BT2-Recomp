#include "common.h"

extern s32 func_002C2CF8(s32 arg0, s32 arg1, u8 *fn);
extern u8 func_002D5268[];
extern u8 func_002D52D8[];
extern u8 func_002D5358[];
extern u8 func_002D53C8[];

void func_002C2A90(s32 arg0, s32 arg1, s32 *arg2) {
    if (arg1 != 0) {
        arg2[0] = func_002C2CF8(arg0, arg1, func_002D5268);
        arg2[1] = func_002C2CF8(arg0, arg1, func_002D52D8);
        arg2[2] = func_002C2CF8(arg0, arg1, func_002D5358);
        arg2[3] = func_002C2CF8(arg0, arg1, func_002D53C8);
    }
}
