#include "common.h"

extern f32 D_00386BC4;
extern f32 D_00386BC8;
extern f32 D_00386BCC;
extern f32 D_00386BD0;
extern f32 D_00386BD4;
extern f32 D_00386BD8;
extern f32 D_00386BDC;
extern f32 D_00386BE0;
extern f32 D_00386BE4;

s32 BtlObjXf_Update(void *arg0);
void BtlMember_SubBlast(void *arg0, s32 arg1);
void BtlMove_BrakeVertical(void *arg0);
void func_001F9D78(void *arg0, s32 arg1);
s32 func_001F9FB0(void *arg0, s32 arg1);
s32 func_001FA0A0(void *arg0, s32 arg1, s32 arg2);
s32 func_001FA1D0(void *arg0, f32 farg0);
s32 func_001FA2E0(void *arg0);
f32 func_001FA318(void *arg0);
void func_001FCD80(void *arg0);
void func_00206958(void *arg0, s64 arg1);
void func_00206EA0(void *arg0);
void func_00206FE0(void *arg0, s32 arg1);
void func_00207068(void *arg0);
void func_0020FC38(void *arg0, s32 arg1);
void func_00210618(void *arg0, s32 arg1);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212638(void *arg0);
void func_00212DD8(void *arg0, s32 arg1);
void func_00215068(void *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, void *arg0, s32 arg1);
void func_00216208(void *arg0, f32 farg0, f32 farg1);
void func_00216678(void *arg0);
void func_00216890(void *arg0, f32 farg0, f32 farg1);
s32 func_0023F500(void *arg0, s32 arg1);

void func_0023A490(void *arg0) {
    s32 r;
    f32 f20;

    if (*(s32 *)((u8 *)arg0 + 0x8CC) == 1) {
        func_002113C0(arg0, 0xC, 0x20, 1);
        func_0020FC38(arg0, 0x31);
        func_00206958(arg0, (s32)((s64)0x8000 << 41));
    }

    r = BtlObjXf_Update(arg0);
    if (r >= 0x1B7) {
        if (r == 0x1B7) {
            goto case1B7;
        }
        goto tail868;
    }
    if (r >= 0x1B5) {
        goto defaultblk;
    }
    if (r == 0x2B) {
        goto case2B;
    }
    if (r == 0x2C) {
        goto case2C;
    }
    goto tail868;

case2B:
    func_001FA0A0(arg0, 0x2C, 0);
    if (func_001FA318(arg0) < 0.5f) {
        goto brake728;
    }
    func_00216890(arg0, D_00386BC4, D_00386BC8);
    goto tail868;

case2C:
    if (func_001F9FB0(arg0, 0) != 0) {
        func_00216890(arg0, 0.0f, D_00386BCC);
        if (func_00211310(arg0, 0xC, 0x40) != 0) {
            if (*(s32 *)((u8 *)arg0 + 0x8DC) & 1) {
                func_001F9D78(arg0, 0x1B5);
                func_002113C0(arg0, 0xE, 2, 1);
            } else {
                func_001F9D78(arg0, 0x1B6);
                func_002113C0(arg0, 0xE, 4, 1);
            }
            func_002113C0(arg0, 9, 0x4000, 1);
            func_002113C0(arg0, 9, 0x400000, 1);
            func_002113C0(arg0, 1, 0x20000, 1);
            func_002113C0(arg0, 0xC, 0x80, 1);
        }
    } else {
        func_00216890(arg0, D_00386BD0, D_00386BD4);
    }
    func_002113C0(arg0, 1, 0x100000, 1);
    goto tail868;

defaultblk:
    if (func_001FA2E0(arg0) != 0) {
        func_002113C0(arg0, 0xC, 0x100, 1);
        func_00206FE0(arg0, BtlObjXf_Update(arg0));
    }
    if (func_001F9FB0(arg0, 0) != 0) {
        if (func_00211310(arg0, 0xC, 0x200) != 0) {
            func_001F9D78(arg0, 0x1B7);
            BtlMember_SubBlast(arg0, func_0023F500(arg0, func_00212638(arg0)));
            func_002113C0(arg0, 0xC, 0x400, 1);
        }
    }
    func_00207068(arg0);

brake728:
    BtlMove_BrakeVertical(arg0);
    goto tail868;

case1B7:
    if (func_001FA2E0(arg0) != 0) {
        func_002113C0(arg0, 0xC, 0x800, 1);
        func_00206EA0(arg0);
        func_002113C0(arg0, 0xE, 8, 1);
        func_00206958(arg0, (s32)((s64)0x8000 << 42));
        if (*(s32 *)((u8 *)arg0 + 0x8DC) & 1) {
            func_00210618(arg0, 0x3C21);
        } else {
            func_00210618(arg0, 0x3C23);
        }
    } else {
        func_002113C0(arg0, 0xC, 0x800, 0);
    }
    if (func_001FA1D0(arg0, D_00386BD8) != 0) {
        func_00212DD8(arg0, 0x22);
    }
    if (func_001F9FB0(arg0, 0) != 0) {
        func_002113C0(arg0, 9, 0x800000, 1);
        func_002113C0(arg0, 3, 0x1000, 1);
        func_002113C0(arg0, 1, 0x20000, 1);
        func_002113C0(arg0, 0xE, 1, 1);
        func_001FCD80(arg0);
        func_002113C0(arg0, 0xE, 0x40, 1);
    }
    func_00216678(arg0);
    goto tail868;

tail868:
    f20 = D_00386BDC;
    func_00215068(arg0, 5, 0xC, D_00386BE0, f20);
    func_00215E88(f20, arg0, 7);
    func_00216208(arg0, 0.0f, D_00386BE4);
    func_002113C0(arg0, 9, 0x10000, 1);
    func_002113C0(arg0, 9, 4, 1);
    func_002113C0(arg0, 3, 0xF, 1);
    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xD, 0x10, 1);
    func_002113C0(arg0, 0xD, 1, 1);
    func_002113C0(arg0, 3, 0x800, 1);
    func_002113C0(arg0, 9, 0x200000, 1);
    func_002113C0(arg0, 1, 0x800, 1);
    func_002113C0(arg0, 1, 0x40, 1);
    func_002113C0(arg0, 0xF, 0x100000, 1);
    func_00206958(arg0, 0x10000);
}
