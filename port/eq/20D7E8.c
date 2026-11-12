#include "common.h"

/* 0x0020D7E8: if (!func_00211310(a0, 0, 1)) return; func_002113C0(a0, 1, 0x80, 1);
   p = BtlChar_GetPos(a0); p->+0xCC = f12; q = BtlChar_GetPos(a0); q->+0xD0 = f13. */
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BtlChar_GetPos(s32 arg0);

void func_0020D7E8(s32 a0, f32 f12, f32 f13) {
    u8 *p;

    if (func_00211310(a0, 0, 1) == 0) {
        return;
    }
    func_002113C0(a0, 1, 0x80, 1);
    p = (u8 *)BtlChar_GetPos(a0);
    *(f32 *)(p + 0xCC) = f12;
    p = (u8 *)BtlChar_GetPos(a0);
    *(f32 *)(p + 0xD0) = f13;
}
