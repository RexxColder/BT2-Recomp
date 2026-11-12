#include "common.h"

s32 func_002CE760(s32 arg0);
void func_002CEDC0(s32 arg0);

s32 func_002CDE40(u8 *arg0) {
    s32 v = func_002CE760((s32)arg0);

    if (v == 0) {
        *(s32 *)(arg0 + 0x4C) = 6;
        func_002CEDC0((s32)arg0);
        v = 0;
    }
    return v;
}
