#include "common.h"

void func_002CF6F0(s32 arg0);

void func_002CF6A8(s32 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        func_002CF6F0(arg0 + i * 0xDD8);
    }
}
