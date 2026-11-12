#include "common.h"

/* 0x00284888: func_00312680(a0, a0 + 0x30, f = *(f32 *)(a0 + 0x50)); then tail func_00312638(a0, a0, a0 + 0x10). */
s32 func_00312680(s32 arg0, s32 arg1, f32 farg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);

void func_00284888(s32 a0) {
    f32 f;

    f = *(f32 *)((u8 *)a0 + 0x50);
    func_00312680(a0, a0 + 0x30, f);
    func_00312638(a0, a0, a0 + 0x10);
}
