#include "common.h"

extern f32 D_00385BD0;
extern f32 D_00385BD4;
extern f32 D_00385BD8;
extern f32 D_00385BDC;
extern f32 D_00385BE0;

s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA0A0(s32 a0, s32 a1, s32 a2);
void BtlChar_SetVibration(u8 *arg0, f32 arg1, f32 arg2);
f32 func_001FA318(u8 *arg0);
s32 func_001F9FB0(s32 arg0, s32 arg1);
s32 func_001FA2E0(s32 arg0);
void func_001FCD80(void *arg0);
f32 func_001FA308(void *a0);
s32 BtlObjAnim_QueryEvent(u8 *a, s32 b, s32 c, s32 d);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 a0);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 f12, f32 f13);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00206958(u8 *a0, s64 a1);

s32 func_00219B38(u8 *obj) {
    s32 kind;
    s32 n;
    s32 ev;
    s32 r;
    f32 level;
    f32 margin;

    kind = BtlObjXf_Update((s32)obj);
    level = D_00385BD0;

    switch (kind) {
    case 86:
    case 89:
    case 92:
    case 95:
    case 98:
    case 101:
        n = BtlObjXf_Update((s32)obj);
        func_001FA0A0((s32)obj, n + 1, 0);
        func_002113C0((s32)obj, 9, 0x10000, 1);
        func_002113C0((s32)obj, 9, 4, 1);
        break;
    case 87:
    case 90:
    case 93:
    case 96:
    case 99:
    case 102:
        n = BtlObjXf_Update((s32)obj);
        if (func_001FA0A0((s32)obj, n + 1, 0) != 0) {
            BtlChar_SetVibration(obj, 1.0f, D_00385BD4);
        }
        *(f32 *)(obj + 0x9B0) = func_001FA318(obj);
        func_00206958(obj, (s64)0x40000);
        func_002113C0((s32)obj, 9, 0x10000, 1);
        func_002113C0((s32)obj, 9, 4, 1);
        break;
    case 88:
    case 91:
    case 94:
    case 97:
    case 100:
    case 103:
        func_001F9FB0((s32)obj, 0);
        if (func_001FA2E0((s32)obj) != 0) {
            func_001FCD80(obj);
        }
        level = 0.0f;
        margin = func_001FA308(obj) - 15.0f;
        ev = BtlObjAnim_QueryEvent(*(u8 **)(obj + 0x1530), 2, 0, 1);
        if (margin < (f32)ev) {
            func_00206958(obj, (s64)0x40000);
        }
        break;
    default:
        break;
    }

    r = func_00211310((s32)obj, 5, 4);
    if (r == 0) {
        level = 0.0f;
    }
    func_00215068(obj, 5, 12, D_00385BD8, 0.5f);
    func_00215E88(D_00385BDC, (s32)obj, 2);
    func_00216208((s32)obj, level, D_00385BE0);
    func_00216678((s32)obj);
    func_002113C0((s32)obj, 9, 0x200, 1);
    func_002113C0((s32)obj, 15, 0x40, 1);

    if (func_00211310((s32)obj, 0, 0x100) != 0) {
        return func_002113C0((s32)obj, 0, 2, 1);
    }
    return 0;
}
