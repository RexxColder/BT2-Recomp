#include "common.h"

s32 func_001E2020(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0);
s32 func_001E2F60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0);

/* f12 passes through to the tail-called func_001E2020 / func_001E2F60 */
s32 func_001E1258(u8 *arg0, s32 arg1, s32 arg2, f32 farg0) {
    if (*(u8 *)(arg0 + 0x16B) != 0) {
        if (*(u8 *)(arg0 + 0x16C) == 0) {
            return func_001E2020((s32)(arg0 + 0x10), (s32)(arg0 + 0x60), arg1, *(s32 *)(arg0 + 0x194), arg2 & 0xFF, farg0);
        }
        return func_001E2F60((s32)(arg0 + 0x10), (s32)(arg0 + 0x60), arg1, arg2 & 0xFF, farg0);
    }
    return 0;
}
