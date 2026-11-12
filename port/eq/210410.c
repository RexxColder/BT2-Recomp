#include "common.h"

extern f32 D_00385A08;

s32 BtlObjXf_Update(u8 *arg0);
s32 func_001FA3A8(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
void func_0020FAD0(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2);
s32 func_00210DD8(s32 arg0, s32 arg1);
s32 func_00210D98(s32 arg0);
s32 func_0025FBE8(s32 arg0, s64 arg1);
s32 func_002411E0(s32 arg0, s32 arg1);
void func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

void func_00210410(u8 *arg0) {
    s32 sp[2];
    s32 s1;
    s32 s2;
    s32 s3;
    s32 temp_v0;
    s32 var_v1;

    s3 = 2;
    temp_v0 = func_001FA3A8(BtlObjXf_Update(arg0));
    s2 = (temp_v0 & 0x04000000) ? 0x2D : -1;
    if (temp_v0 & 0x08000000) {
        s2 = 0x31;
        s3 = 3;
    }
    if (temp_v0 & 0x10000000) {
        s2 = 0x35;
        s3 = 4;
    }
    if (s2 >= 0) {
        var_v1 = *(s32 *)(arg0 + 0x1534);
        if (temp_v0 & 0x10) {
            var_v1 = func_00210DD8((s32)arg0, temp_v0);
        }
        s1 = var_v1 + 3;
        func_0020FAD0(200.0f, D_00385A08, BtlChar_GetPos((s32)arg0), (s32)&sp[0], (s32)&sp[1]);

        if (func_0025FBE8(*(s32 *)(arg0 + 0x1530), 0x10000) != 0) {
            func_00297FE0(s1, s2, sp[0], sp[1], 0);
        }
        if (func_0025FBE8(*(s32 *)(arg0 + 0x1530), 0x20000) != 0) {
            if (func_002411E0((s32)arg0, s3) & 0x100) {
                if (!(func_00210D98((s32)arg0) & 0x80)) {
                    func_00297FE0(s1, s2 + 1, sp[0], sp[1], 0);
                }
            } else {
                func_00297FE0(s1, s2 + 1, sp[0], sp[1], 0);
            }
        }
        if (func_0025FBE8(*(s32 *)(arg0 + 0x1530), 0x40000) != 0) {
            if (func_002411E0((s32)arg0, s3) & 0x200) {
                if (!(func_00210D98((s32)arg0) & 0x80)) {
                    func_00297FE0(s1, s2 + 2, sp[0], sp[1], 0);
                }
            } else {
                func_00297FE0(s1, s2 + 2, sp[0], sp[1], 0);
            }
        }
        if (func_0025FBE8(*(s32 *)(arg0 + 0x1530), 0x80000) != 0) {
            func_00297FE0(s1, s2 + 3, sp[0], sp[1], 0);
        }
    }
}
