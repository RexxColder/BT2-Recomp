#include "common.h"

void func_00113E20(u8 *arg0, s32 arg1, s32 arg2);

void func_00113E48(u8 *arg0, s32 arg1, s32 arg2) {
    s32 b = arg1 & 0xFF;

    while ((*(s32 *)arg0 & 2) == 0) {
        func_00113E20(arg0, b, arg2);
        arg0 += 0x60;
    }
}
