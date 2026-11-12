#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);
void func_002F5620(s32 arg0, s32 arg1);

void func_002BE8A0(u8 *arg0) {
    s32 *s1;
    s32 s0;
    s32 v0;

    s1 = *(s32 **)(arg0 + 0x2004);
    s0 = s1[0];
    v0 = func_002D07B0((s32)arg0, 0x1B);
    if (s1[0x44 / 4] != v0) {
        s1[0x44 / 4] = v0;
        func_002F5620(s0, v0);
    }
}
