#include "m2c_macros.h"

s32 func_00217488(void *arg0);
s32 BtlObjXf_Update(void *arg0);
void *BtlChar_GetPos(void *arg0);
void func_00212C40(void *arg0, s32 *arg1, s32 *arg2);
s32 func_0025FBE8();
void func_00101608(void *a0, void *a1, s32 a2, s32 a3, s32 t0);
void func_00267550(void *a0, s32 a1, s32 a2);
void func_00207208(void *a0, s32 a1);
void func_001017F0(s32 a0, s32 a1);

/* Lock-on effect for the character at arg0 (only in the 0x34..0x36 state, with BtlObjXf_Update == 0x1B5):
 * the stick-like position from func_00212C40 is turned into two clamped values (s0 = -15..15, s1 = -960..0),
 * three flag tests pick the effect id (0x5F..0x61), and the effect is driven through the unit at +0x1530. */
void BtlChar_UpdateLockFx(u8 *arg0) {
    s32 sp[2];
    u8 *o;
    void *pos;
    f32 fx;
    f32 fy;
    s32 s0;
    s32 s1;
    s32 s3;
    s32 a2v;
    s32 r;

    o = arg0;
    s3 = -1;
    r = func_00217488(o);
    if (!(r >= 0x34 && r < 0x37)) {
        return;
    }
    if (BtlObjXf_Update(o) != 0x1B5) {
        return;
    }

    pos = BtlChar_GetPos(o);
    func_00212C40(pos, &sp[0], &sp[1]);
    fx = ((f32)sp[0] / 127.0f - 1.0f) * 200.0f;
    fy = ((f32)sp[1] * 0.015625f - 1.0f) * 15.0f;
    s0 = (s32)fy;
    s1 = (s32)fx;
    s0 = (s0 < 0x10) ? s0 : 15;
    s0 = (s0 < -15) ? -15 : s0;
    a2v = (s1 > 0);
    s1 = (s1 > 0) ? 0 : s1;
    s1 = (s1 < -960) ? -960 : s1;

    r = func_0025FBE8(*(u8 **)(o + 0x1530), 0x8000, a2v, -15);
    s3 = (r != 0) ? 0x5F : s3;
    r = func_0025FBE8(*(u8 **)(o + 0x1530), 0x8000LL << 24);
    s3 = (r != 0) ? 0x60 : s3;
    r = func_0025FBE8(*(u8 **)(o + 0x1530), 0x20000);
    s3 = (r != 0) ? 0x61 : s3;

    if (s3 >= 0) {
        func_00101608(*(void **)(o + 0x1534), *(void **)(*(u8 **)(o + 0x1530) + 4), s3, s1, s0);
        func_00267550(*(void **)(o + 0x1530), 2, s3);
        if (*(u8 *)(o + 0x1434) != 0) {
            func_00207208(o, s3);
        }
    }
    if (func_0025FBE8(*(u8 **)(o + 0x1530), 0x40000) != 0) {
        func_001017F0(0x3C20, s1);
    }
}
