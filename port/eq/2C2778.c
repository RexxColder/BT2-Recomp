#include "common.h"

s32 func_002D4658(s32 arg0, s32 arg1);
s32 func_002D4A48(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D4F58(s32 arg0, s32 arg1);
void func_002C28D0(s32 arg0, s32 arg1);
void func_002C2960(s32 arg0, s32 arg1);
s32 func_002C2A18(s32 arg0, s32 arg1, s32 arg2);
void func_002C2A90(s32 arg0, s32 arg1, s32 arg2);
void func_002C2B28(s32 arg0, s32 arg1, s32 arg2);

void func_002C2778(s32 arg0, u8 *arg1) {
    s32 sp[4];
    s32 v;
    s32 sum;
    s32 v1;

    v = func_002D4658(arg0, (s32)sp);
    sp[0] = (v == 0) ? 0 : sp[0];
    if (sp[0] == 0) {
        return;
    }
    if (func_002D4A48(arg0, (s32)&sp[1], (s32)&sp[2]) == 0) {
        sp[1] = 0;
        sp[2] = 0;
    }
    *(s32 *)(arg1 + 0x4) = sp[1];
    *(s32 *)(arg1 + 0x8) = sp[2];
    sum = sp[1] * 100 + sp[2];
    v = func_002D4F58(arg0, (s32)&sp[3]);
    v1 = (v == 0) ? 0 : sp[3];
    if (sum < 0x6E) {
        v1 = -v1;
    }
    sp[3] = v1;
    *(s32 *)(arg1 + 0xC) = sp[3];
    func_002C28D0(arg0, (s32)arg1);
    func_002C2960(arg0, (s32)(arg1 + 0x20));
    *(s32 *)(arg1 + 0x3C) = func_002C2A18(arg0, 0xBD, 0xBD);
    *(s32 *)(arg1 + 0x40) = func_002C2A18(arg0, 0xBF, 0xBF);
    *(s32 *)(arg1 + 0x44) = func_002C2A18(arg0, 0xC0, 0xDF);
    *(s32 *)(arg1 + 0x48) = func_002C2A18(arg0, 0xE0, 0xEF);
    func_002C2A90(arg0, *(s32 *)(arg1 + 0x44), (s32)(arg1 + 0x4C));
    func_002C2B28(arg0, *(s32 *)(arg1 + 0x48), (s32)(arg1 + 0x5C));
    *(s32 *)(arg1 + 0x0) = 1;
}
