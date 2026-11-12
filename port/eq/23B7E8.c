#include "common.h"

extern f32 D_00386C04;
extern f32 D_00386C08;
extern f32 D_00386C0C;
extern f32 D_00386C10;
extern f32 D_00386C14;
extern f32 D_00386C18;

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BtlChar_GetPos(s32 arg0);
s32 func_001F9FB0(s32 arg0, s32 arg1);
s32 func_001FA1D0(s32 arg0, f32 farg0);
void func_00206958(s32 arg0, s64 arg1);
void func_0020FC38(s32 arg0, s32 arg1);
void BtlChar_SetSmallVibration(s32 arg0, f32 farg0);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
void func_00209730(s32 arg0, s32 arg1);
void func_00210FD0(s32 arg0, s32 arg1);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_002608E8(s32 arg0);
f32 func_002086B0(s32 arg0);
f32 func_00210D10(s32 arg0);
void func_00210868(s32 arg0, s32 arg1);
f32 sinf(f32 arg0);
f32 cosf(f32 arg0);

void func_0023B7E8(s32 arg0) {
    f32 o00[4];
    f32 o10[4];
    f32 o20[4];
    f32 o30[4];
    f32 o40[4];
    f32 f20;
    f32 f21;
    f32 tmp;
    s32 st;
    s32 p1;
    s32 p2;

    if (func_00211310(arg0, 2, 1) != 0) {
        func_002113C0(arg0, 3, 0xF, 1);
        func_002113C0(arg0, 1, 0x4000000, 1);
        p1 = BtlChar_GetPos(arg0);
        *(s32 *)(p1 + 0xC0) = 0;
        p2 = BtlChar_GetPos(arg0);
        *(s32 *)(p2 + 0xC4) = 0;

        st = *(s32 *)(arg0 + 0x8C0);
        *(s32 *)(arg0 + 0x8C0) = st + 1;
        if (st == 6) {
            if (func_00211310(arg0, 0, 1) != 0) {
                f21 = 1.0f;
                f20 = func_002086B0(*(s32 *)(arg0 + 0x1534)) + 0.0f;
                tmp = func_00210D10(arg0);
                f20 = f20 + tmp;
                func_00210868(arg0, (s32)o30);
                tmp = sinf(o30[1]);
                o40[0] = -tmp * f20;
                o40[1] = 0.0f;
                tmp = cosf(o30[1]);
                o40[2] = -tmp * f20;
                o40[3] = 0.0f;
                p1 = BtlChar_GetPos(arg0);
                p2 = BtlChar_GetPos(arg0);
                func_00312638(p1, p2, (s32)o40);
                func_00215068(arg0, 1, 9, D_00386C18, f21);
                func_00215E88(arg0, 3, f21);
                func_002113C0(arg0, 3, 0x800, 1);
                func_00206958(arg0, 0x4000);
                func_002113C0(arg0, 0xE, 0x20, 1);
                func_002113C0(arg0, 0xF, 0x20, 1);
                func_002113C0(arg0, 1, 0x20000, 1);
            }
        } else if (st < 7) {
            if (st == 5) {
                if (func_00211310(arg0, 0, 1) != 0) {
                    func_00209730(*(s32 *)(arg0 + 0x1534), (s32)o00);
                    func_00210FD0(arg0, (s32)o10);
                    func_00312650((s32)o20, (s32)o10, (s32)o00);
                    p1 = BtlChar_GetPos(arg0);
                    p2 = BtlChar_GetPos(arg0);
                    func_00312638(p1, p2, (s32)o20);
                    func_002608E8(*(s32 *)(arg0 + 0x1530));
                    func_002113C0(arg0, 3, 0x800, 1);
                    func_002113C0(arg0, 0xE, 0x20, 1);
                    func_002113C0(arg0, 0xF, 0x20, 1);
                    func_002113C0(arg0, 1, 0x20000, 1);
                }
            }
        } else if (st == 7) {
            if (func_00211310(arg0, 0, 1) != 0) {
                func_002113C0(arg0, 0xE, 0x40, 1);
                func_002113C0(arg0, 9, 0x200, 1);
            }
        } else if (st == 0xB) {
            *(s32 *)(arg0 + 0x8DC) |= 1;
        }

        if (*(s32 *)(arg0 + 0x8C0) < 9) {
            func_002113C0(arg0, 9, 0x4000, 1);
        }
    } else {
        func_001F9FB0(arg0, 0);
        if (func_001FA1D0(arg0, D_00386C04) != 0) {
            func_00206958(arg0, 0x2000);
            func_0020FC38(arg0, 0x20);
            BtlChar_SetSmallVibration(arg0, D_00386C08);
        }
        f20 = D_00386C0C;
        func_00215068(arg0, 5, 0xD, D_00386C10, f20);
        func_00215E88(arg0, 7, f20);
        func_00216208(arg0, 0.0f, D_00386C14);
        func_00216678(arg0);
    }

    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xD, 0x10, 1);
}
