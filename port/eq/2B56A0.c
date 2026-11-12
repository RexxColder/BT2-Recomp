#include "common.h"

void func_002C5718(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002B5848(void *arg0, void *arg1);

void func_002B56A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];

    func_002C5718(arg0, arg1, arg2, (s32)sp);
    func_002B5848(sp, (void *)arg3);
}
