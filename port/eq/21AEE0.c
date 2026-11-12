#include "common.h"

extern f32 D_00385C58;
extern f32 D_00385C5C;
extern f32 D_00385C60;
extern f32 D_00385C64;

s32 BtlObjXf_Update(u8 *arg0);
void func_001FA0A0(u8 *arg0, s32 arg1, s32 arg2);
void func_001F9FB0(u8 *arg0, s32 arg1);
s32 func_001FA2E0(u8 *arg0);
s32 func_0023F2D8(u8 *arg0);
void func_00212DD8(u8 *arg0, s32 arg1);
void func_00215068(u8 *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4);
void func_00215E88(u8 *arg0, s32 arg1, f32 arg2);
void func_00216208(u8 *arg0, f32 arg1, f32 arg2);
void func_00216678(u8 *arg0);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);

/* jtbl_00370050, indexed by (BtlObjXf_Update() - 0x56), 18 entries:
 * idx % 3 == 0 -> .L0021AF20, == 1 -> .L0021AF78 (end), == 2 -> .L0021AF48. */
void func_0021AEE0(u8 *arg0) {
    s32 s1;
    s32 v;
    s32 r;

    s1 = 0;
    v = BtlObjXf_Update(arg0);
    switch (v - 0x56) {
    case 0:
    case 3:
    case 6:
    case 9:
    case 12:
    case 15:
        s1 = 1;
        r = BtlObjXf_Update(arg0);
        func_001FA0A0(arg0, r + 2, 0);
        break;
    case 2:
    case 5:
    case 8:
    case 11:
    case 14:
    case 17:
        func_001F9FB0(arg0, 0);
        if (func_001FA2E0(arg0) != 0) {
            r = func_0023F2D8(arg0);
            func_00212DD8(arg0, r);
        }
        break;
    default:
        break;
    }

    if (s1 != 0) {
        func_00215068(arg0, 1, 0xC, D_00385C58, 0.5f);
    } else {
        func_00215068(arg0, 5, 0xC, D_00385C5C, 0.5f);
    }
    func_00215E88(arg0, 2, D_00385C60);
    func_00216208(arg0, 0.0f, D_00385C64);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
