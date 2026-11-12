#include "common.h"

extern u8 D_002C3630[] __attribute__((section(".data")));
extern f32 D_00386B1C;
extern f32 D_00386B20;
extern f32 D_00386B24;
extern f32 D_00386B28;
extern f32 D_00386B2C;
extern f32 D_00386B30;
extern f32 D_00386B34;
extern f32 D_00386B38;
extern f32 D_00386B3C;
extern f32 D_00386B40;
extern f32 D_00386B44;
extern f32 D_00386B48;

s32 BtlObjXf_Update(void *arg0);
void *BtlChar_GetPos(void *arg0);
void BtlAnim_SetBlend(f32 farg0, void *arg0);
f32 BtlCharApi_GetHeight(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
void BtlMove_BrakeVertical(void *arg0);
void func_00212DD8(void *arg0, s32 arg1);
void func_001F9D78(void *arg0, s32 arg1);
void func_001F9F90(void *arg0);
s32 func_001F9FB0(void *arg0, s32 arg1);
s32 func_001FA0A0(void *arg0, s32 arg1, s32 arg2);
void func_001FA110(void *arg0, s32 arg1);
f32 func_001FA318(void *arg0);
void func_001FC3B0(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5,
                   void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6,
                   s32 arg7, s32 stack0, s32 stack1, s32 stack2, s32 stack3, s32 stack4);
void func_00206958(void *arg0, s64 arg1);
void func_0020FC38(void *arg0, s32 arg1);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
void func_00216890(f32 farg0, f32 farg1, void *arg0);
void func_00216678(void *arg0);
void func_00215068(f32 farg0, f32 farg1, void *arg0, s32 arg1, s32 arg2);
void func_00215E88(f32 farg0, void *arg0, s32 arg1);
void func_00216208(f32 farg0, f32 farg1, void *arg0);
s32 func_0023F410(void *arg0);

void func_00239088(u8 *arg0) {
    u8 *s0;
    u8 *s1;
    u8 *pos;
    s32 r;
    s32 v0;
    s32 v1;
    f32 f0;
    f32 f12;
    f32 f16;
    f32 f20;
    f32 f21;

    s0 = arg0;
    s1 = arg0 + 0x8C0;
    f21 = 0.0f;
    if (*(s32 *)(s0 + 0x8CC) == 1) {
        func_00212DD8(s0, 0x10);
    }
    r = BtlObjXf_Update(s0);

    if (r == 0x3B) {
        func_001FA110(s0, 0);
        func_00216890(D_00386B24, D_00386B28, s0);
        func_002113C0(s0, 1, 0x100000, 1);
        func_00206958(s0, 8);
        v0 = *(s32 *)s1 + 1;
        *(s32 *)s1 = v0;
        if (v0 == 0xF) {
            func_00206958(s0, 0x2000);
            func_0020FC38(s0, 0x20);
        }
        v1 = *(s32 *)s1;
        v0 = 1;
        if (v1 >= 0x10) {
            func_002113C0(s0, 9, 0x4000, 1);
            v1 = *(s32 *)s1;
            v0 = (v1 < 0x1F);
        }
        if (v0 == 0) {
            if (func_00211310(s0, 0xC, 4) != 0) {
                func_001F9D78(s0, 0x39);
                func_002113C0(s0, 0xC, 8, 1);
                func_00206958(s0, 0x20);
                *(s32 *)s1 = 0;
            }
        }
    } else if (r < 0x3C) {
        if (r == 0x32 || r == 0) {
            func_001F9FB0(s0, 0);
            f0 = func_001FA318(s0);
            if (D_00386B3C < f0) {
                *(s32 *)(s0 + 0x8DC) = *(s32 *)(s0 + 0x8DC) | 1;
            }
            func_00216678(s0);
        } else if (r == 0x39) {
            v1 = *(s32 *)s1;
            if (v1 < 0xF) {
                v0 = v1 + 1;
                *(s32 *)s1 = v0;
                if (v0 == 1) {
                    func_002113C0(s0, 0xC, 0x10, 1);
                    func_002113C0(s0, 1, 0x20000, 1);
                    pos = BtlChar_GetPos(s0);
                    f0 = D_00386B30;
                    f12 = *(f32 *)(pos + 0xB4) - f0;
                    BtlUtil_WrapAngle(f12);
                    f0 = BtlCharApi_GetHeight(*(s32 *)(s0 + 0x1534));
                    f20 = f0;
                    f16 = f0 * 1.5f;
                    func_001FC3B0(f20, f21, D_00386B34, f21, f16, f21,
                                  s0, D_002C3630, D_002C3630, D_002C3630, D_002C3630, D_002C3630, D_002C3630,
                                  3, 3, 0, 3, 0xF, 0xC5);
                } else {
                    func_002113C0(s0, 0xC, 0x10, 0);
                }
                v1 = *(s32 *)s1;
                if (v1 == 0xF) {
                    func_00206958(s0, 0x4000);
                    func_0020FC38(s0, 0x20);
                    func_00212DD8(s0, 0xF);
                }
            } else {
                v0 = func_00211310(s0, 0, 2);
                v0 = func_001FA0A0(s0, (v0 != 0) ? 0x32 : 0, 0);
                if (v0 != 0) {
                    BtlAnim_SetBlend(D_00386B38, s0);
                }
            }
            f0 = func_001FA318(s0);
            if (f0 < 0.5f) {
                func_002113C0(s0, 9, 0x4000, 1);
            }
            func_00216678(s0);
        }
    } else if (r < 0x100) {
        if (r == 0xFF) {
            if (func_001FA0A0(s0, 0x41, 0) != 0) {
                func_002113C0(s0, 2, 0x100, 1);
                BtlAnim_SetBlend(D_00386B1C, s0);
                func_002113C0(s0, 0xC, 1, 1);
            }
            BtlMove_BrakeVertical(s0);
        } else if (r == 0x41) {
            if (func_001F9FB0(s0, 0) != 0) {
                func_001F9F90(s0);
                BtlAnim_SetBlend(D_00386B20, s0);
                if ((func_0023F410(s0) & 0x1000) == 0) {
                    if ((func_0023F410(s0) & 0x10) != 0) {
                        func_0020FC38(s0, 0x1D);
                    } else {
                        func_0020FC38(s0, 0x1C);
                    }
                }
            }
            BtlMove_BrakeVertical(s0);
        }
    } else if (r == 0x1A4) {
        func_001FA110(s0, 0);
        v0 = *(s32 *)s1 + 1;
        v1 = (v0 < 0x1E);
        *(s32 *)s1 = v0;
        if (v1 != 0) {
            f21 = D_00386B2C;
        }
        if (!(v0 < 0x1F)) {
            if (func_00211310(s0, 0xC, 4) != 0) {
                func_001F9D78(s0, 0x39);
                func_002113C0(s0, 0xC, 8, 1);
                *(s32 *)s1 = 0;
            }
        }
        BtlMove_BrakeVertical(s0);
    }

    f20 = D_00386B40;
    func_00215068(D_00386B44, f20, s0, 5, 0xC);
    func_00215E88(f20, s0, 3);
    func_00216208(f21, D_00386B48, s0);
    func_002113C0(s0, 9, 0x10000, 1);
    func_002113C0(s0, 9, 4, 1);
    func_002113C0(s0, 3, 0xF, 1);
    func_002113C0(s0, 0xD, 8, 1);
    func_002113C0(s0, 0xD, 0x10, 1);
    func_002113C0(s0, 0xD, 1, 1);
    func_002113C0(s0, 3, 0x800, 1);
    func_002113C0(s0, 9, 0x200000, 1);
    func_002113C0(s0, 1, 0x800, 1);
    func_002113C0(s0, 1, 0x40, 1);
    func_002113C0(s0, 9, 0x8000000, 1);
    func_002113C0(s0, 0xF, 0x100000, 1);
    *(u8 *)(s0 + 0x1014) = 1;
}
