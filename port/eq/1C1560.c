#include "common.h"

u8 *func_001C14A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

u8 *func_001C1560(s32 arg0, s32 arg1, s16 arg2, s16 arg3, f32 farg0) {
    u8 *obj = func_001C14A0(arg0, arg1, arg2, arg3, 0);
    if (obj != 0) {
        *(f32 *)(obj + 0xC) = farg0;
    }
    return obj;
}
