#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
f32 BtlParam_GetTypeValueC(s32 arg0);
s32 BtlParam_IsTypeSetA(s32 arg0);
s32 func_00203C58(s32 arg0, s64 arg1);
f32 func_00210A48(s32 arg0);
f32 func_00210A98(s32 arg0);
s32 func_00210D98(u8 *arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
f32 fabsf(f32 farg0);
extern f32 D_00385B24;

s32 func_00217A78(u8 *arg0) {
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 s5;
    f32 f20;
    f32 f21;
    f32 f0;
    f32 f4;

    s1 = 0;
    s5 = (func_00210D98(arg0) >> 7) & 1;
    s4 = func_00211310((s32)arg0, 0xA, 0x100);
    s3 = BtlParam_IsTypeSetA((s32)arg0);
    s2 = func_00211310((s32)arg0, 0, 0x400);
    f21 = func_00210A48((s32)arg0);
    f20 = fabsf(func_00210A98((s32)arg0));
    if (f20 <= *(f32 *)(arg0 + 0x101C)) {
        f0 = BtlParam_GetTypeValueC((s32)arg0);
        f4 = *(f32 *)(arg0 + 0x1020) * (((1.0f - f0) * (1.0f - (f20 / D_00385B24))) + f0);
        if (f21 < f4) {
            s1 = (s2 == 0);
            if ((s3 != 0) && (BtlObjXf_Update((s32)arg0) == 0x197)) {
                if (s5 == 0) {
                    s1 = (s4 != 0) ? s1 : 1;
                }
            }
            if (func_00203C58((s32)arg0, 0x100000) != 0) {
                if ((BtlObjXf_Update((s32)arg0) ^ 0x197) == 0) {
                    s1 = 1;
                }
            }
        }
    }
    return s1;
}
