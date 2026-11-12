#include "common.h"

s32 func_00266938(s32 arg0);

s32 func_00267518(s32 arg0) {
    s32 v;

    v = 0;
    if (*(s32 *)((u8 *)arg0 + 0xE00) != 0) {
        v = 1;
        if (func_00266938(arg0) == 0) {
            v = 0;
        }
    }
    return v;
}
