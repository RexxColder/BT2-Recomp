#include "common.h"

void func_002D7030(s32 arg0, s32 arg1);

void func_002D6FD0(u8 *arg0, s32 arg1) {
    s32 half;
    s32 t;

    t = (s32)((u32)arg1 >> 31) + arg1;
    t = (t >> 1) * 2;
    half = t >> 1;
    func_002D7030((s32)(arg0 + 0x4), t);
    func_002D7030((s32)(arg0 + 0x14), half);
    func_002D7030((s32)(arg0 + 0x24), half);
}
