#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define FLDF(p, off) (*(f32 *)((u8 *)(p) + (off)))

s32 BtlObjXf_Update(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_001F9FB0(s32 arg0, s32 arg1);
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_001FA2E0(s32 arg0);
s32 func_002174B8(s32 arg0);
s32 func_00203888(s32 arg0, s32 arg1, s32 arg2);
s32 func_00240398(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002177A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void func_00209268(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 sinf(f32 farg0);
f32 cosf(f32 farg0);

extern f32 D_00386240;
extern f32 D_00386244;
extern f32 D_00386248;
extern f32 D_00386250;
extern f32 D_00386254;
extern f32 D_0038624C;

void func_002260A0(s32 arg0) {
    s32 sp[4];
    s32 s2;
    s32 s0;
    s32 v;
    f32 f;

    s2 = (func_00211310(arg0, 0, 2) != 0) ? 0x32 : 0;
    v = BtlObjXf_Update(arg0);
    if (v == 0x32 || v == 0) {
        func_001F9FB0(arg0, 1);
    } else if (v >= 0x7D && v < 0x7F) {
        if (func_002174B8(arg0) != -1) {
            func_001F9FB0(arg0, 0);
        } else if (func_001FA0A0(arg0, s2, 0) != 0) {
            BtlAnim_SetBlend(arg0, D_00386240);
        }
        s0 = BtlObjXf_Update(arg0) + 2;
        v = BtlObjXf_Update(arg0) + 4;
        func_002177A8(arg0, s0, v, 1);
        if (func_001FA2E0(arg0) != 0) {
            func_00203888(arg0, func_00240398(arg0), 0);
        }
    }
    func_00215068(arg0, 1, 0xC, D_00386244, 0.5f);
    func_00215E88(arg0, 7, D_00386248);
    func_00216208(arg0, 0.0f, D_0038624C);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 0xD, 8, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
    if (func_00211310(arg0, 0, 1) != 0) {
        func_00208DE8(FLD(arg0, 0x1534), (s32)sp, 0x11);
        func_00209268(D_00386250, D_00386254, FLD(arg0, 0x1534), arg0 + 0xA00, (s32)sp, 0x11);
        return;
    }
    f = sinf(FLDF(BtlChar_GetPos(arg0), 0xB4));
    FLDF(arg0, 0xA04) = 0.0f;
    FLDF(arg0, 0xA00) = f;
    f = cosf(FLDF(BtlChar_GetPos(arg0), 0xB4));
    FLDF(arg0, 0xA0C) = 0.0f;
    FLDF(arg0, 0xA08) = f;
}
