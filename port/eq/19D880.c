#include "common.h"

extern f32 D_00384D74;
extern f32 D_00384D78;

s32 Rand_IntRange(s32 a0, s32 a1);
f32 Rand_FloatRange(f32 f12, f32 f13);
s32 func_00129C28(u8 *a0, s32 a1);
s32 func_0019D850(u8 *a0, s32 a1, s32 a2, s32 a3);

s32 func_0019D880(u8 *obj, u8 *A, u8 *B, s32 p3, s32 p4) {
    s32 s0;
    s32 r;
    u16 flags;

    r = Rand_IntRange(0, A[0xF]);
    *(u16 *)(obj + 0x4) = (u16)(A[0xE] + r);
    r = Rand_IntRange(0, A[0x11]);
    *(u16 *)(obj + 0x6) = (u16)~(A[0x10] + r);
    func_00129C28(obj + 0x20, p3);
    obj[0x2] = A[0x2] & 1;

    flags = *(u16 *)(A + 0x2);
    if (flags & 0x2) {
        if (Rand_IntRange(0, 1) == 1) {
            obj[0x1] |= 0x10;
        }
    }
    if (flags & 0x4) {
        if (Rand_IntRange(0, 1) == 1) {
            obj[0x1] |= 0x20;
        }
    }
    if (flags & 0x8) {
        obj[0x1] |= 0x1;
    }
    if (flags & 0x10) {
        *(f32 *)(obj + 0x14) = Rand_FloatRange(D_00384D74, D_00384D78);
    }

    r = Rand_IntRange(0, B[0x8]);
    s0 = r & 0xFF;
    r = Rand_IntRange(0, B[0x4]);
    obj[0x18] = (u8)(s0 + B[0x0] + r);
    r = Rand_IntRange(0, B[0x5]);
    obj[0x19] = (u8)(s0 + B[0x1] + r);
    r = Rand_IntRange(0, B[0x6]);
    s0 = s0 + B[0x2] + r;
    obj[0x1A] = (u8)s0;
    r = Rand_IntRange(0, B[0x7]);
    obj[0x1B] = (u8)(B[0x3] + r);
    *(f32 *)(obj + 0x1C) = 1.0f;

    /* tail call (j func_0019D850): a0 = obj, a1 = t0, a2 = A[0xD], a3 = bit 8 of A[2..3] */
    return func_0019D850(obj, p4, A[0xD], (flags >> 8) & 1);
}
