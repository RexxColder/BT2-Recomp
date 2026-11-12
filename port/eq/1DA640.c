#include "common.h"

void func_00129E08(s32 arg0, s64 arg1);

void func_001DA640(u8 *arg0) {
    s64 sp[2];

    sp[1] = *(s64 *)(arg0 + 8);
    sp[0] = *(s64 *)arg0;
    func_00129E08((s32)sp, sp[0]);
}
