#include "common.h"

void func_00270678(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0);

void func_0026EEF8(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, f32 farg0) {
    if (*arg1 >= 0) {
        if (!(farg0 < 0.0f)) {
            func_00270678(*(s32 *)(arg0 + 0x1C), (s32)arg1, arg2, arg3, farg0);
        }
    }
}
