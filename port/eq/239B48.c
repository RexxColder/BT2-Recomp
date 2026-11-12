#include "common.h"

/* 0x00239B48: per-frame handler of a battle character for the short state set 0 / 36 / 57 / 230..233
 * (idle, a get-hit style state with ground contact test, its recovery, and a falling state), followed by the common
 * per-frame flag setup. Returns the character position block (BtlChar_GetPos). */
extern u8 D_002C3630[] __attribute__((section(".data")));

s32 func_002113C0(u8 *o, s32 a, s32 b, s32 c);
extern s32 BtlObjXf_Update();
s32 func_00211310(u8 *o, s32 a, s32 b);
s32 func_001FA0A0(u8 *o, s32 a, s32 b);
void func_001FA110(u8 *o, s32 a);
void func_00215068(u8 *o, s32 a, s32 b, f32 f12, f32 f13);
void func_00215E88(u8 *o, s32 a, f32 f);
void func_00216208(u8 *o, f32 a, f32 b);
void func_00216678(u8 *o);
void BtlMove_BrakeVertical(u8 *o);
s32 func_001F9D78(u8 *o, s32 a);
s32 func_002765A8(s32 a0, u8 *a1, u8 *a2, s32 a3);
s32 func_001FA2E0(u8 *o);
void func_00215CA8(u8 *o, u8 *p, f32 a, f32 b);
s32 func_00206958(u8 *o, s64 a);
s32 func_0023F410(u8 *o);
void func_0020FC38(u8 *o, s32 a);
f32 BtlCharApi_GetHeight(s32 chr);
u8 *BtlChar_GetPos(u8 *o);
f32 BtlUtil_WrapAngle(f32 a);
s32 func_001FC3B0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);
void func_00212DD8(u8 *o, s32 a);
void func_00215E30(u8 *o, f32 a, f32 b);
void func_001FBE80(u8 *o, f32 a, f32 b);
void BtlChar_Vibrate(u8 *o, f32 a, f32 b);

extern f32 D_00386B70, D_00386B74, D_00386B78, D_00386B7C, D_00386B80, D_00386B84, D_00386B88, D_00386B8C;
extern f32 D_00386B90, D_00386B94, D_00386B98, D_00386B9C, D_00386BA0, D_00386BA4, D_00386BA8, D_00386BAC;
extern f32 D_00386BB0, D_00386BB4, D_00386BB8;

u8 *func_00239B48(u8 *obj) {
    s32 *cnt = (s32 *)(obj + 0x8C0);
    u8 sp[0x70];
    f32 *p = (f32 *)(sp + 0x30);
    f32 *A = (f32 *)(sp + 0x50);
    f32 *B = (f32 *)(sp + 0x60);
    s32 state;
    s32 hit;
    u32 fl;
    f32 f20, h1, h2, yaw;
    u8 *pos;
    u8 *pos2;
    s32 chr;

    if (*(s32 *)(obj + 0x8CC) == 1) {
        func_002113C0(obj, 12, 1, 1);
    }
    state = BtlObjXf_Update(obj);

    if (state == 57) {
        f20 = D_00386BA4;
        func_001FA0A0(obj, 0, 0);
        func_00215068(obj, 5, 12, D_00386BA8, f20);
        func_00215E88(obj, 7, f20);
        func_00216208(obj, 0.0f, D_00386BAC);
        func_00216678(obj);
    } else if (state >= 58) {
        if (state < 234 && state >= 230) {
            f20 = D_00386B70;
            func_001FA110(obj, 0);
            func_00215068(obj, 5, 12, D_00386B74, f20);
            func_00215E88(obj, 7, f20);
            func_00216208(obj, 0.0f, D_00386B78);
            BtlMove_BrakeVertical(obj);
            *cnt = *cnt + 1;
            if (*cnt >= 0x1F) {
                if (func_00211310(obj, 12, 4)) {
                    func_001F9D78(obj, 0x24);
                    func_002113C0(obj, 12, 8, 1);
                    *cnt = 0;
                }
            }
        }
    } else if (state == 0) {
        func_001FA110(obj, 0);
        *cnt = *cnt + 1;
        if (*cnt >= 0x1F) {
            func_002113C0(obj, 11, 0x80, 1);
            func_002113C0(obj, 12, 1, 0);
            func_002113C0(obj, 12, 4, 0);
            func_002113C0(obj, 12, 8, 0);
            func_002113C0(obj, 12, 0x10, 0);
        }
        f20 = D_00386BB0;
        func_00215068(obj, 5, 12, D_00386BB4, f20);
        func_00215E88(obj, 7, f20);
        func_00216208(obj, 0.0f, D_00386BB8);
        func_00216678(obj);
    } else if (state == 36) {
        func_002765A8(*(s32 *)(obj + 0x1534), sp + 0x30, sp + 0x40, 0);
        func_001FA110(obj, 0);
        if (func_001FA2E0(obj)) {
            func_00215CA8(obj, sp + 0x30, D_00386B7C, 1.0f);
        } else {
            func_00215068(obj, 5, 13, D_00386B80, D_00386B84);
        }
        func_00215E88(obj, 3, D_00386B88);
        func_00216208(obj, D_00386B8C, D_00386B90);
        BtlMove_BrakeVertical(obj);
        func_002113C0(obj, 1, 0x2000, 1);
        func_00206958(obj, 8);
        func_00206958(obj, 0x800);
        if (func_001FA2E0(obj)) {
            func_002113C0(obj, 12, 0x10, 1);
            if (func_0023F410(obj) & 0x10) {
                func_0020FC38(obj, 0x1D);
            } else {
                func_0020FC38(obj, 0x1C);
            }
            func_002113C0(obj, 1, 0x20000, 1);
            chr = *(s32 *)(obj + 0x1534);
            A[0] = p[0];
            h1 = BtlCharApi_GetHeight(chr) * D_00386B94;
            A[2] = p[2];
            B[0] = A[0];
            A[1] = p[1] - h1;
            h2 = BtlCharApi_GetHeight(*(s32 *)(obj + 0x1534));
            B[2] = A[2];
            B[1] = A[1] - h2 * 0.5f;
            pos = BtlChar_GetPos(obj);
            yaw = BtlUtil_WrapAngle(*(f32 *)(pos + 0xB4) + D_00386B98);
            func_001FC3B0(obj, (s32)A, (s32)D_002C3630, (s32)A, (s32)D_002C3630, (s32)B, (s32)D_002C3630, -1,
                          -1, -1, 3, 15, 197,
                          yaw, 0.0f, 0.0f, 0.0f, BtlCharApi_GetHeight(*(s32 *)(obj + 0x1534)), 0.0f);
        } else {
            func_002113C0(obj, 12, 0x10, 0);
        }
        if (!func_001FA2E0(obj)) {
            hit = func_00211310(obj, 0, 4) != 0;
            fl = *(u32 *)(*(u8 **)(obj + 0x1530) + 0xE54);
            if ((fl & 0x20) != 0 && (fl & 0x40) == 0) {
                hit = 1;
            }
            if (hit) {
                func_001F9D78(obj, 0x39);
                func_002113C0(obj, 0, 2, 0);
                func_00206958(obj, 0x4000000000ll);
                func_0020FC38(obj, 0x25);
                func_00212DD8(obj, 0xF);
                pos = BtlChar_GetPos(obj);
                pos2 = BtlChar_GetPos(obj);
                *(f32 *)(pos + 0xC0) = 0.0f;
                func_00215E30(obj, *(f32 *)(pos2 + 0x14), 0.0f);
                pos = BtlChar_GetPos(obj);
                yaw = BtlUtil_WrapAngle(*(f32 *)(pos + 0xB4) + D_00386B9C);
                h1 = BtlCharApi_GetHeight(*(s32 *)(obj + 0x1534));
                func_001FC3B0(obj, (s32)D_002C3630, (s32)D_002C3630, (s32)D_002C3630, (s32)D_002C3630,
                              (s32)D_002C3630, (s32)D_002C3630, 17, 17, 17, 17, 1, 197,
                              yaw, 0.0f, 0.0f, 0.0f, h1 * 1.5f, 0.0f);
                func_001FBE80(obj, 3.0f, D_00386BA0);
                BtlChar_Vibrate(obj, 1.0f, 0.5f);
                *cnt = 0;
            }
        }
    }

    func_002113C0(obj, 9, 0x10000, 1);
    func_002113C0(obj, 9, 4, 1);
    func_002113C0(obj, 3, 0xF, 1);
    func_002113C0(obj, 13, 8, 1);
    func_002113C0(obj, 13, 0x10, 1);
    func_002113C0(obj, 13, 1, 1);
    func_002113C0(obj, 3, 0x800, 1);
    func_002113C0(obj, 9, 0x200000, 1);
    func_002113C0(obj, 1, 0x800, 1);
    func_002113C0(obj, 1, 0x40, 1);
    func_002113C0(obj, 15, 0x100000, 1);
    *(u8 *)(obj + 0x1014) = 1;
    pos = BtlChar_GetPos(obj);
    pos2 = BtlChar_GetPos(obj);
    *(f32 *)(pos + 0xD4) = *(f32 *)(pos2 + 0xB0);
    return pos2;
}
