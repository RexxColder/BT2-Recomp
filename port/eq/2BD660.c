#include "common.h"

void func_002F1C48(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F1DD8(s32 arg0);
void func_002F2280(s32 arg0, s32 arg1);

void func_002BD660(s32 arg0, s32 arg1) {
    func_002F1DD8(arg0);
    func_002F1C48(arg0, arg1, 0, 0, 0xFFFFF);
    func_002F2280(arg0, 0xFFFFF);
}
