#include "common.h"

s32 func_002DDF60(s32 arg0, void *arg1, s32 arg2);
void **func_00303D48(s32 arg0, s32 arg1);

s32 func_002DDDF8(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3) {
    s32 temp_s0;
    s32 ret;
    void **temp_v0;
    u8 *vt;
    s32 (*fn1)(void *, s32);
    void (*fn2)(void *, void *);

    temp_v0 = func_00303D48(arg1[0], arg1[1]);
    if (temp_v0 == NULL) {
        return -1;
    }
    temp_s0 = func_002DDF60(arg0, temp_v0, arg3);
    vt = *(u8 **)temp_v0;
    fn1 = *(s32 (**)(void *, s32))(vt + 0x24);
    ret = fn1(temp_v0, 1);
    *arg2 = arg1[1] - ret;
    vt = *(u8 **)temp_v0;
    fn2 = *(void (**)(void *, void *))(vt + 0xC);
    fn2(temp_v0, vt);
    return temp_s0;
}
