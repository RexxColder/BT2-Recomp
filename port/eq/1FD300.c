#include "m2c_macros.h"

extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_001FD300(u8 *arg0) {
    u8 *s1;
    s8 a0;
    s32 v0;
    u8 *t;

    s1 = arg0 + 0xBE0;
    *(s32 *)(arg0 + 0xB48) = 1;
    if (func_00211310((s32)arg0, 0, 0x80) != 0) {
        func_002113C0((s32)arg0, 4, 2, 0);
        func_002113C0((s32)arg0, 4, 8, 0);
        func_002113C0((s32)arg0, 4, 4, 0);
    }
    if (func_00211310((s32)arg0, 2, 2) != 0) {
        func_002113C0((s32)arg0, 4, 1, 0);
    }
    a0 = *(s8 *)(*(u8 **)(arg0 + 0x1530) + 0xD7D);
    v0 = *(s32 *)(s1 + 0x14);
    if (a0 >= 0) {
        if (v0 != a0) {
            func_002113C0((s32)arg0, 4, 1, 0);
            *(s32 *)(arg0 + 0x1438) = *(s32 *)(arg0 + 0x1438) + 1;
        }
    } else {
        if (v0 >= 0) {
            if (func_00211310((s32)arg0, 4, 1) == 0 && func_00211310((s32)arg0, 2, 2) == 0) {
                t = *(u8 **)(arg0 + 0x1530);
                if (*(s8 *)(t + 0xD7D) == ~*(s8 *)(t + 0xD7C)) {
                    func_002113C0((s32)arg0, 4, 8, 1);
                }
            }
        }
        func_002113C0((s32)arg0, 4, 1, 0);
    }
    *(s32 *)(s1 + 0x14) = *(s8 *)(*(u8 **)(arg0 + 0x1530) + 0xD7D);
}
