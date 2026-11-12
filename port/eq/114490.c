#include "common.h"

void func_00114468(u8 *arg0, s32 arg1, s32 arg2);

void func_00114490(u8 *arg0, s32 arg1, s32 arg2) {
    s32 b = arg2 & 0xFF;

    while ((*(s32 *)arg0 & 2) == 0) {
        func_00114468(arg0, arg1, b);
        arg0 += 0x60;
    }
}
