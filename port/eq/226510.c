#include "common.h"

#define F32(p, off) (*(f32 *)((p) + (off)))

extern f32 D_00386268;
extern f32 D_0038626C;
extern f32 D_00386270;
extern f32 D_00386274;
extern f32 D_00386278;

s32 BtlObjXf_Update(u8 *arg0);
s32 func_001FA0A0(u8 *arg0, s32 arg1, s32 arg2);
s32 func_001F9FB0(u8 *arg0, s32 arg1);
f32 func_001FA318(u8 *arg0);
s32 func_001F9D78(u8 *arg0, s32 arg1);
s32 func_001FA2E0(u8 *arg0);
s32 func_00240398(u8 *arg0);
s32 func_00203888(u8 *arg0, s32 arg1, s32 arg2);
s32 func_00212DD8(u8 *arg0, s32 arg1);
void func_002177A8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BtlPad_Test48(u8 *arg0, s32 arg1);
void func_00215068(u8 *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(u8 *arg0, s32 arg1, f32 farg0);
void func_00216208(u8 *arg0, f32 farg0, f32 farg1);
void func_00216678(u8 *arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
s32 func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void func_00209268(s32 arg0, u8 *arg1, u8 *arg2, s32 arg3, f32 farg0, f32 farg1);
u8 *BtlChar_GetPos(u8 *arg0);

void func_00226510(u8 *arg0) {
    u8 sp[0x10];
    u8 *s1;
    u8 *p;
    s32 v;
    s32 r1;
    s32 r2;
    s32 s0;
    f32 f0;
    f32 f20;

    s1 = arg0;
    v = BtlObjXf_Update(s1);
    if (v == 0x88) {
        func_001FA0A0(s1, 0x89, 0);
        f0 = func_001FA318(s1);
        F32(s1, 0xA1C) = f0;
        r1 = BtlObjXf_Update(s1);
        s0 = r1 + 3;
        r2 = BtlObjXf_Update(s1);
        func_002177A8(s1, s0, r2 + 6, 1);
        func_002113C0(s1, 5, 0x400, 1);
        if (BtlPad_Test48(s1, 1) == 0) {
            func_001F9D78(s1, 0x89);
        }
    } else if (v < 0x89) {
        if (v == 0x87) {
            func_001FA0A0(s1, 0x88, 0);
            r1 = BtlObjXf_Update(s1);
            s0 = r1 + 3;
            r2 = BtlObjXf_Update(s1);
            func_002177A8(s1, s0, r2 + 6, 1);
            func_002113C0(s1, 5, 0x400, 1);
        }
    } else if (v == 0x89) {
        func_001F9FB0(s1, 0);
        r1 = BtlObjXf_Update(s1);
        s0 = r1 + 3;
        r2 = BtlObjXf_Update(s1);
        func_002177A8(s1, s0, r2 + 6, 0);
        if (func_001FA2E0(s1) != 0) {
            v = func_00240398(s1);
            func_00203888(s1, v, 0);
            func_00212DD8(s1, 0x25);
        }
    }

    func_00215068(s1, 1, 0xC, D_00386268, 0.5f);
    func_00215E88(s1, 7, D_0038626C);
    func_00216208(s1, 0.0f, D_00386270);
    func_00216678(s1);
    func_002113C0(s1, 9, 0x200, 1);
    func_002113C0(s1, 0xD, 8, 1);
    func_002113C0(s1, 0xF, 0x40, 1);
    if (func_00211310(s1, 0, 0x100) != 0) {
        func_002113C0(s1, 0, 2, 1);
    }
    if (func_00211310(s1, 0, 1) != 0) {
        func_00208DE8(*(s32 *)(s1 + 0x1534), sp, 0x11);
        func_00209268(*(s32 *)(s1 + 0x1534), s1 + 0xA00, sp, 0x11, D_00386274, D_00386278);
    } else {
        f20 = 0.0f;
        p = BtlChar_GetPos(s1);
        f0 = sinf(F32(p, 0xB4));
        F32(s1, 0xA04) = f20;
        F32(s1, 0xA00) = f0;
        p = BtlChar_GetPos(s1);
        f0 = cosf(F32(p, 0xB4));
        F32(s1, 0xA0C) = f20;
        F32(s1, 0xA08) = f0;
    }
}
