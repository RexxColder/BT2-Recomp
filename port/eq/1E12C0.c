#include "common.h"

/* f12/f13 (farg0, farg1) pass through to the tail-called func_001E2598 / func_001E35F8 */
s32 func_001E2598(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0, f32 farg1);
void func_001E35F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);

void func_001E12C0(u8 *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1) {
    if (arg0[0x16B] != 0) {
        if (arg0[0x16C] == 0) {
            func_001E2598((s32)(arg0 + 0x10), (s32)(arg0 + 0x60), arg1, *(s32 *)(arg0 + 0x194), arg2 & 0xFF, farg0, farg1);
            return;
        }
        func_001E35F8((s32)(arg0 + 0x10), (s32)(arg0 + 0x60), arg1, arg2 & 0xFF, farg0, farg1);
    }
}
