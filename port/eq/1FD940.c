#include "common.h"

extern u8 *D_00387930;
extern f32 D_00385864;
extern f32 D_00385868;

s32 func_00211270(void);
u8 *func_00211288(s32 a0);
s32 func_00210DD8(u8 *a0);
s32 func_00211310(u8 *a0, s32 a1, s32 a2);
s32 func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
s32 func_00217BD0(u8 *a0);
void func_0020FC38(u8 *a0, s32 a1);
s32 BtlObjXf_Update(u8 *a0);
s32 func_001FA3A8(s32 a0);
s32 func_002411E0(u8 *a0, s32 a1);
s32 func_0023F440(u8 *a0);
s32 func_00206958(u8 *a0, s64 a1);
s32 func_001FD1F0(u8 *a0);
u8 *BtlChar_GetPos(u8 *a0);
f32 BtlUtil_WrapAngle(f32 a);
s32 func_00203C58(u8 *a0, s64 a1);
void func_00203888(u8 *a0, s32 a1, s32 a2);
s32 BtlMember_IsKiEmpty(u8 *a0);
void func_00203968(u8 *a0, s32 a1);
s32 BtlMember_IsHealthEmpty_2127F8(u8 *a0);
u8 *BtlMember_GetActiveGauge(u8 *a0);
s32 func_00241050(u8 *a0, s32 a1);
s32 func_00241BE0(u8 *a0, s32 a1);
s32 func_00241990(u8 *a0, s32 a1);
s32 BtlChar_FrameMod(s32 a0);
s32 func_002418E8(u8 *a0, s32 a1);
f32 func_00241A00(u8 *a0, s32 a1);
f32 func_00241A58(u8 *a0, s32 a1);

#define W(p, o) (*(s32 *)((p) + (o)))
#define FL(p, o) (*(f32 *)((p) + (o)))
#define B(p, o) (*(u8 *)((p) + (o)))

s32 func_001FD940(void) {
    s32 s6, s0, s3, s4, s5, s7, v0, v1;
    u8 *s1, *s2, *p0, *p1;
    f32 f0;

    s7 = 0x10031;
    for (s6 = 0; s6 < func_00211270(); s6++) {
        s1 = func_00211288(s6);
        v0 = func_00210DD8(s1);
        s2 = func_00211288(v0);
        if (func_00211310(s1, 7, 0x80000) && func_00211310(s2, 7, 0x80000)
            && (func_00217BD0(s1) || func_00217BD0(s2))
            && func_00211310(s1, 0, 0x400000) && func_00211310(s2, 0, 0x400000)) {
            func_002113C0(s1, 7, 0x4000, 1);
            func_002113C0(s2, 7, 0x4000, 1);
            func_002113C0(s1, 3, 0xE, 1);
            func_002113C0(s2, 3, 0xE, 1);
            W(s1, 0x988) = 6;
            W(s2, 0x988) = 6;
            W(s1, 0x98C) = 0;
            W(s2, 0x98C) = 0;
            func_0020FC38(s1, 0x4F);
            func_0020FC38(s2, 0x4B);
            return 1;
        }
        if (!func_00211310(s1, 3, 0x200)) continue;
        if (!func_00217BD0(s1)) continue;
        s5 = 0;
        v0 = BtlObjXf_Update(s1);
        s0 = func_001FA3A8(v0);
        v0 = BtlObjXf_Update(s2);
        s3 = func_001FA3A8(v0);
        if (s0 & 0x4000000) { s5 = 0x4E20; W(s1, 0xA70) = 2; }
        if (s0 & 0x8000000) { s5 = 0x4E20; W(s1, 0xA70) = 3; }
        if (s0 & 0x10000000) { s5 = 0x9C40; W(s1, 0xA70) = 4; }
        s4 = func_002411E0(s1, W(s1, 0xA70));
        if (func_00211310(s2, 3, 1) || (s3 & 0x100000)) {
            func_002113C0(s1, 4, 0x1000000, 1);
            continue;
        }
        if (func_0023F440(s2) == 4 && !(s4 & 0x100000)) {
            func_002113C0(s1, 4, 0x2000000, 1);
            func_002113C0(s1, 9, 0x4000000, 1);
            func_00206958(s1, 0x8000000);
            continue;
        }
        v0 = 0;
        if (func_001FD1F0(s2) == 8) {
            p0 = BtlChar_GetPos(s1);
            p1 = BtlChar_GetPos(s2);
            f0 = BtlUtil_WrapAngle(FL(p0, 0xB4) - FL(p1, 0xB4));
            f0 = __builtin_fabsf(f0);
            if (D_00385864 < f0 && !(s4 & 1) && !func_00203C58(s1, 0x10000000)) {
                func_002113C0(s1, 4, 0x2000000, 1);
                func_002113C0(s1, 9, 0x4000000, 1);
                func_00206958(s2, 0x1000000);
                func_002113C0(s2, 4, 0x2000, 1);
                func_002113C0(s2, 6, 1, 1);
                p0 = BtlChar_GetPos(s1);
                f0 = BtlUtil_WrapAngle(FL(p0, 0xB4) + D_00385868);
                W(s2, 0xB68) = 0;
                FL(s2, 0xB64) = f0;
                func_00203888(s2, s5, 0);
                if (BtlMember_IsKiEmpty(s2)) {
                    func_002113C0(s2, 0, 0x4000, 1);
                }
                continue;
            }
        }
        v0 = W(s2, 0x1178);
        if (v0 > 0) {
            if (s3 & s7) {
                func_002113C0(s1, 4, 0x1000000, 1);
                func_002113C0(s2, 4, 0x80000000, 1);
                func_00203968(s2, 0xC350);
                continue;
            }
        }
        v1 = W(s2, 0xAC8);
        if (v1 > 0 && (s3 & s7)) {
            W(s2, 0xAC8) = v1 - 1;
            func_002113C0(s1, 4, 0x1000000, 1);
            func_002113C0(s2, 4, 0x80000000, 1);
            v1 = W(s2, 0xAD0);
            if (v1 == 0) {
                func_002113C0(s2, 0xF, 0x400, 1);
            } else if (v1 == 1) {
                func_002113C0(s2, 0xF, 0x800, 1);
            }
            continue;
        }
        v1 = W(s2, 0xACC);
        if (v1 > 0 && (s3 & s7)) {
            W(s2, 0xACC) = v1 - 1;
            func_002113C0(s1, 4, 0x1000000, 1);
            func_002113C0(s2, 4, 0x40000000, 1);
            v1 = W(s2, 0xAD0);
            if (v1 == 0) {
                func_002113C0(s2, 0xF, 0x400, 1);
            } else if (v1 == 1) {
                func_002113C0(s2, 0xF, 0x800, 1);
            }
            continue;
        }
        if (func_00203C58(s2, 0x100000000LL) && !BtlMember_IsHealthEmpty_2127F8(s2)
            && func_00211310(s2, 0, 0x4000) && B(BtlMember_GetActiveGauge(s2), 0x2B)) {
            func_002113C0(s1, 4, 0x1000000, 1);
            func_002113C0(s2, 4, 0x20000000, 1);
            func_002113C0(s2, 0, 0x4000, 0);
            continue;
        }
        if (!func_00211310(s1, 0, 0x400000)) {
            func_002113C0(s1, 4, 0x1000000, 1);
            continue;
        }
        func_002113C0(s1, 4, 0x800000, 1);
        s0 = 0;
        s5 = 1;
        W(s1, 0xA74) = func_00241050(s1, W(s1, 0xA70));
        W(s1, 0xA80) = func_00241BE0(s1, W(s1, 0xA70));
        W(s1, 0xA7C) = func_00241990(s1, W(s1, 0xA70));
        func_002113C0(s1, 6, 1, 1);
        p0 = BtlChar_GetPos(s1);
        f0 = FL(p0, 0xB4);
        W(s1, 0xB68) = 0;
        s3 = (s4 & 0x8000) != 0;
        FL(s1, 0xB64) = f0;
        if (s4 & 0x80) {
            s0 = BtlChar_FrameMod(2) != 0;
        }
        B(s1, 0xA85) = (u8)s0;
        W(s1, 0xA78) = func_002418E8(s1, W(s1, 0xA70));
        if (s4 & 0x800) {
            B(s1, 0xA84) = (u8)s5;
            FL(s1, 0xA88) = func_00241A00(s1, W(s1, 0xA70));
            FL(s1, 0xA8C) = func_00241A58(s1, W(s1, 0xA70));
        } else {
            B(s1, 0xA84) = 0;
            W(s1, 0xA88) = 0;
            W(s1, 0xA8C) = 0;
        }
        W(s2, 0xB48) = 0x20;
        W(s2, 0xA70) = W(s1, 0xA70);
        W(s2, 0xA80) = -1;
        W(s2, 0xA74) = W(s1, 0xA74);
        W(s2, 0xA7C) = W(s1, 0xA7C);
        W(s2, 0xA78) = W(s1, 0xA78);
        B(s2, 0xA84) = B(s1, 0xA84);
        FL(s2, 0xA88) = FL(s1, 0xA88);
        FL(s2, 0xA8C) = FL(s1, 0xA8C);
        B(s2, 0xA85) = B(s1, 0xA85);
        func_002113C0(s2, 6, 1, 1);
        f0 = FL(s1, 0xB64);
        FL(s2, 0xB64) = f0;
        FL(s2, 0xB5C) = f0;
        FL(s2, 0xB68) = FL(s1, 0xB68);
        B(s2, 0xB54) = (u8)s3;
        func_002113C0(s1, 3, 0xE, 1);
        func_002113C0(s2, 3, 0xE, 1);
        v1 = W(D_00387930, 8);
        if (!(v1 & 4)) {
            W(D_00387930, 8) = v1 | 4;
            func_002113C0(s1, 0x10, 0x4000000, 1);
        }
        func_002113C0(s1, 9, 0x200000, 1);
        return 1;
    }
    return 0;
}
