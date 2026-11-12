#include "common.h"

s32 BtlObjXf_Update(u8 *a0);
void func_001FA380(u8 *a0, f32 farg0);
s32 func_002174B8(u8 *a0);
void func_001F9FB0(u8 *a0, s32 a1);
s32 func_00211310(u8 *a0, s32 a1, s32 a2);
s32 func_001FA0A0(u8 *a0, s32 a1, s32 a2);
void BtlAnim_SetBlend(u8 *a0, f32 farg0);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 farg0, f32 farg1);
void func_00215E88(u8 *a0, s32 a1, f32 farg0);
void func_00216208(u8 *a0, f32 farg0, f32 farg1);
void func_00216678(u8 *a0);
s32 func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
extern f32 D_00385C24;
extern f32 D_00385C28;
extern f32 D_00385C2C;
extern f32 D_00385C30;

s32 func_0021A958(u8 *arg0) {
    s32 r;
    s32 res;
    s32 v0;

    r = BtlObjXf_Update(arg0);
    if (r < 0x4C) {
        if (r >= 0x48) {
            func_001FA380(arg0, 2.0f);
            res = func_002174B8(arg0);
            if (res != -1) {
                func_001F9FB0(arg0, 0);
            } else {
                v0 = func_00211310(arg0, 0, 2);
                v0 = func_001FA0A0(arg0, (v0 != 0) ? 0x32 : 0, 0);
                if (v0 != 0) {
                    BtlAnim_SetBlend(arg0, D_00385C24);
                }
            }
        } else if (r == 0 || r == 0x32) {
            func_001F9FB0(arg0, 1);
        }
    } else if (r == 0x4C) {
        func_001F9FB0(arg0, 0);
    }
    func_00215068(arg0, 5, 0xC, D_00385C28, 0.5f);
    func_00215E88(arg0, 2, D_00385C2C);
    func_00216208(arg0, 0.0f, D_00385C30);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 1, 0x800000, 1);
    v0 = func_00211310(arg0, 0, 0x100);
    if (v0 == 0) {
        return 0;
    }
    return func_002113C0(arg0, 0, 2, 1);
}
