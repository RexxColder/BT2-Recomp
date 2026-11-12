#include "common.h"

s32 func_002FC550(s32 arg0);
s32 func_002FC7E8(s32 arg0, s32 arg1, s32 arg2);
void func_002FB820(void);
void func_00331710(s32 arg0);
extern u8 D_0037DE60[] __attribute__((section(".data")));

void func_002FB878(s32 arg0) {
    s32 sp[4];
    u8 *base;
    s32 s0;
    s32 s2;

    base = (u8 *)arg0;
    s2 = 0;
    sp[0] = 1;
    while (sp[0] == 1) {
        func_002FC550(0x1100);
        s0 = func_002FC7E8(*(s32 *)(base + 0x30), 1, (s32)sp);
        func_002FC550(0x1101);
        if (s0 < 0) {
            *(s32 *)(base + 0x34) = s0;
            *(s8 *)(base + 2) = 9;
            return;
        }
        s2 += 1;
        func_002FB820();
        if (s2 > 0x9000) {
            func_00331710((s32)D_0037DE60);
            return;
        }
    }
}
