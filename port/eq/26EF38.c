#include "common.h"

void func_002707C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);

s32 func_0026EF38(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1) {
    s32 v = *(s32 *)arg1;

    if (v < 0) {
        return v;
    }
    if (farg0 < 0.0f) {
        return v;
    }
    if (farg1 < 0.0f) {
        return v;
    }
    func_002707C0(*(s32 *)(arg0 + 0x1C), (s32)arg1, arg2, arg3, farg0, farg1);
    return v;
}
