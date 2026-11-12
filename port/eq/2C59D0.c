#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002C3210(s32 arg0);
void func_002DE330(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_002C59D0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (func_002C3210((s32)arg0) != 0) {
        return func_002C2FF0(0, 0xFF000184, arg2, arg3, arg4);
    }
    func_002DE330(*(s32 *)*(u8 **)(arg0 + 0x1FC0), arg1, arg2, arg3, arg4);
    return 0;
}
