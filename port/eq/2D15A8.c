#include "common.h"

void func_002C32B0(s32 *arg0, s32, s32);
void func_002C32C8(s32 *arg0);
s32 func_002D07B0(s32 arg0, s32 arg1);
s32 func_002D1640(s32 arg0, s32 arg1, s32 arg2);

s32 func_002D15A8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    s32 idx;
    s32 *slot;
    s32 (*fp)(s32, s32, s32);
    s32 r;

    func_002C32B0(sp, arg1, arg2);
    idx = func_002D07B0(arg0, 0xF);
    slot = (s32 *)(arg0 + 0xD30 + idx * 4);
    fp = (s32 (*)(s32, s32, s32))(*slot);
    if (fp == NULL) {
        fp = func_002D1640;
    }
    r = fp(arg0, arg1, arg2);
    func_002C32C8(sp);
    return r;
}
