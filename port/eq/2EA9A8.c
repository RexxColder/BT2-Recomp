#include "common.h"

s32 func_002EAA30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_002ED118(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_002ED130(void);

s32 func_002EA9A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 result;

    func_002ED118(arg0, arg1, arg2, arg3, arg4, arg5);
    result = func_002EAA30(arg0, arg1, arg2, arg3, arg4, arg5);
    func_002ED130();
    return result;
}
