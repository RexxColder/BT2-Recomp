#include "common.h"

s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);

void func_001B06D0(void *arg0, void *arg1, s32 arg2, f32 farg0) {
    func_00208DE8((s32)arg1, (s32)arg0, arg2);
    *(f32 *)((u8 *)arg0 + 0xC) = 1.0f;
    *(f32 *)((u8 *)arg0 + 0x4) = (*(f32 *)((u8 *)arg0 + 0x4) - farg0) - 0.0f;
}
