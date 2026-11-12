#include "common.h"

extern f32 D_00386A38;
extern f32 D_00386A3C;
extern f32 D_00386A40;

s32 BtlObjXf_Update(s32 arg0);
s32 func_001F9FB0(s32 arg0, s32 arg1);
s32 func_001FA0A0(s32 a0, s32 a1, s32 a2);
f32 func_001FA318(u8 *arg0);
s32 func_001F9D78(s32 arg0, s32 arg1);
s32 BtlPad_Test4C(u8 *a0, s32 a1);
void func_002182A8(void *a0);
void func_0020FC38(u8 *a0, s32 a1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 f12, f32 f13);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 a0);

/* Shared tail: flag 4 check, then optional 172 event. */
static void tail_check(u8 *obj) {
    if (func_00211310((s32)obj, 4, 0x8000000) != 0) {
        func_001F9D78((s32)obj, 172);
    }
}

/* Branch for the 163 / 415 cases: optional sub-branch on the second update, then the 1.0 store. */
static void branch_k2(u8 *obj) {
    s32 k2 = BtlObjXf_Update((s32)obj);

    if (k2 == 163) {
        func_001FA0A0((s32)obj, 164, 0);
        if (func_001FA318(obj) > 0.5f &&
            (BtlPad_Test4C(obj, 2) || BtlPad_Test4C(obj, 1) || BtlPad_Test4C(obj, 0))) {
            func_001F9D78((s32)obj, 57);
            func_002182A8(obj);
            func_0020FC38(obj, 31);
        }
    } else if (k2 == 415) {
        func_001FA0A0((s32)obj, 416, 0);
    }
    *(f32 *)(obj + 0x9B0) = 1.0f;
    tail_check(obj);
}

s32 func_002371B8(u8 *obj) {
    s32 k;

    k = BtlObjXf_Update((s32)obj);

    if (k == 164) {
        func_001F9FB0((s32)obj, 0);
        tail_check(obj);
    } else if (k < 165) {
        if (k == 57) {
            func_001F9FB0((s32)obj, 0);
            func_002113C0((s32)obj, 5, 0x800, 1);
        } else if (k == 163) {
            branch_k2(obj);
        }
    } else if (k == 415) {
        branch_k2(obj);
    } else if (k < 416) {
        if (k == 172) {
            func_001F9FB0((s32)obj, 0);
        }
    } else if (k == 416) {
        func_001F9FB0((s32)obj, 0);
        tail_check(obj);
    }

    func_00215068(obj, 5, 12, D_00386A38, 0.5f);
    func_00215E88(D_00386A3C, (s32)obj, 2);
    func_00216208((s32)obj, 0.0f, D_00386A40);
    func_00216678((s32)obj);
    return func_002113C0((s32)obj, 9, 0x200, 1);
}
