#include "common.h"

void func_00113E20(s32 *arg0, s32 arg1, s32 arg2) {
    if ((arg1 & 0xFF) == 0) {
        *arg0 = *arg0 | arg2;
        return;
    }
    *arg0 = arg2;
}
