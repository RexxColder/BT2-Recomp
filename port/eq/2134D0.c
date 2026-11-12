#include "common.h"

s32 func_00217488(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
void func_00212C40(s32 arg0, s32 arg1, s32 arg2);
s32 func_0025FBE8();
void func_00101608(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00267550(s32 arg0, s32 arg1, s32 arg2);
void func_001017F0(s32 arg0, s32 arg1);

void func_002134D0(u8 *arg0) {
    s32 sp[2];
    s32 v0;
    s32 a;
    s32 s0;
    s32 s1;
    s32 s3;
    f32 fx;
    f32 fy;

    v0 = func_00217488((s32)arg0);
    if (v0 < 0x37 || v0 >= 0x3A) {
        return;
    }
    if (BtlObjXf_Update((s32)arg0) != 0x1B6) {
        return;
    }
    func_00212C40(BtlChar_GetPos((s32)arg0), (s32)sp, (s32)&sp[1]);

    fx = ((f32)sp[1] * 0.015625f - 1.0f) * 15.0f;
    fy = ((f32)sp[0] / 127.0f - 1.0f) * 200.0f;
    s0 = (s32)fx;
    s1 = (s32)fy;

    s0 = (s0 < 0x10) ? s0 : 0xF;
    s0 = (s0 < -0xF) ? -0xF : s0;
    a = (0 < s1);
    s1 = (a != 0) ? 0 : s1;
    s1 = (s1 < -0x3C0) ? -0x3C0 : s1;

    v0 = func_0025FBE8(*(s32 *)(arg0 + 0x1530), 0x8000, a, -0xF);
    s3 = (v0 != 0) ? 0x62 : -1;
    v0 = func_0025FBE8(*(s32 *)(arg0 + 0x1530), (s64)0x8000 << 24);
    s3 = (v0 != 0) ? 0x63 : s3;

    if (s3 >= 0) {
        func_00101608(*(s32 *)(arg0 + 0x1534), *(s32 *)(*(s32 *)(arg0 + 0x1530) + 4), s3, s1, s0);
        func_00267550(*(s32 *)(arg0 + 0x1530), 2, s3);
    }
    v0 = func_0025FBE8(*(s32 *)(arg0 + 0x1530), 0x40000);
    if (v0 != 0) {
        func_001017F0(0x3C22, s1);
    }
}
