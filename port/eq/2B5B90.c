#include "common.h"

s32 func_002B5B60(s32 arg0);
s32 func_002B5CF8(s32 arg0);
s32 func_002B5D68(s32 arg0);
s32 func_002B5D98(s32 arg0);
s32 func_002D4440(s32 arg0, s32 arg1);
void func_002D4508(s32 arg0);
s32 func_002D4658(s32 arg0, s32 arg1);

void func_002B5B90(s32 arg0, s32 arg1, u8 *arg2) {
    s32 sp[4];
    s32 s0;
    s32 s2;
    s32 s4;
    s32 v;

    *(s32 *)(arg2 + 0x14) = -1;
    if (arg1 >= 0x800 && arg0 != 0) {
        s4 = 2;
        s2 = 0x800;
        do {
            s0 = func_002D4440(arg0 + s2, arg1 - s2);
            s2 += 0x800;
            if (s0 != 0) {
                v = func_002D4658(s0, (s32)sp);
                if (v == 1 && sp[0] == 1) {
                    *(s32 *)(arg2 + 0x14) = func_002B5B60(s0);
                    *(s32 *)(arg2 + 0x18) = func_002B5CF8(s0);
                    *(s32 *)(arg2 + 0x1C) = func_002B5D98(s0);
                    *(s32 *)(arg2 + 0x20) = func_002B5D68(s0);
                    func_002D4508(s0);
                    return;
                }
                *(s32 *)(arg2 + 0x14) = -1;
                *(s32 *)(arg2 + 0x18) = -1;
                func_002D4508(s0);
            }
            s4 += 1;
        } while (s4 < 4);
    }
}
