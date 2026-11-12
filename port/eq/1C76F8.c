#include "common.h"

/* GUESS arity: the asm passes 3 floats (f12..f14), 8 int registers and 5 stack words; ctx.h differs */
void func_001F00A8(f32 fx, f32 fy, f32 fz, s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                   s32 s9, s32 s10, s32 s11, s32 s12, s32 s13);

void func_001C76F8(u8 *arg0) {
    u8 *v1;

    v1 = *(u8 **)(arg0 + 0x38);
    func_001F00A8(*(f32 *)(v1 + 0x20), *(f32 *)(v1 + 0x24), *(f32 *)(v1 + 0x28),
                  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0, 0,
                  0x20, 0x20, 0, 0, *(s32 *)v1);
}
