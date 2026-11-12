#include "common.h"

void func_002D7470(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3);
void func_002D77B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002D7760(s32 arg0, s32 arg1, s32 arg2) {
    s32 out[2];

    func_002D7470(arg0, arg1, &out[0], &out[1]);
    func_002D77B0(arg0, out[0], out[1], arg2);
}
