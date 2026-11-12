#include "common.h"

extern f32 D_00385FB0;
extern f32 D_00385FB4;
extern f32 D_00385FB8;
extern f32 D_00385FBC;
extern f32 D_00385FC0;
extern f32 D_00385FC4;
extern f32 D_00385FC8;

f32 BtlMember_GetHealthRatio(u8 *arg0);
f32 func_001FA318(u8 *arg0);
s32 BtlObjXf_Update(u8 *arg0);
u8 *BtlChar_GetPos(u8 *arg0);
s32 BtlMember_HasKi(u8 *arg0, s32 arg1);
s32 BtlPad_Test48(u8 *arg0, s32 arg1);
s32 BtlPad_Test4C(u8 *arg0, s32 arg1);
void func_00215068(f32 farg0, f32 farg1, u8 *arg0, s32 arg1, s32 arg2);
void func_00215E88(f32 farg0, u8 *arg0, s32 arg1);
void func_00216208(f32 farg0, f32 farg1, u8 *arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
void func_001F9FB0(u8 *arg0, s32 arg1);
void func_001F9D78();
void func_001FA0A0();
void func_001FA110();
void func_0020FC38();
void func_002113C0();
void func_00206958();
void func_00216678();
void func_00217238();
s32 func_00218838();
s32 func_00212878();
s32 func_00212820();
s32 func_0023F420();
s32 func_0023FB58();

void func_00221520(u8 *arg0) {
    f32 f20;
    f32 f21;
    f32 f22;
    f32 ratio;
    f32 t;
    s32 v;
    s32 v2;
    s32 s0;
    s32 rounded;
    s32 cnt;
    u8 *pos;

    f22 = 0.0f;
    f21 = 0.0f;
    v = BtlObjXf_Update(arg0);
    if (v != 0xFA) {
        if (v < 0xFB) {
            if (v >= 0xD2) {
                if (v >= 0xD4) {
                    if (v == 0xF9) {
                        f21 = 0.0f;
                        func_001FA0A0(arg0, 0xFB, 0);
                        f22 = D_00385FBC;
                    }
                } else {
                    func_001FA110(arg0, 0);
                    f21 = D_00385FB0;
                    f22 = D_00385FB4;
                    if (func_00212878() != 0) {
                        ratio = BtlMember_GetHealthRatio(arg0);
                        f21 *= ((1.0f - ratio) * 0.5f) + 0.5f;
                    }
                    cnt = *(s32 *)(arg0 + 0x8C0) - 1;
                    *(s32 *)(arg0 + 0x8C0) = cnt;
                    if (cnt < 0) {
                        if ((func_00212820(arg0) != 0) && (func_00211310(arg0, 1, 0x40000) == 0) &&
                            ((BtlPad_Test48(arg0, 8) != 0) || (func_00212878() != 0))) {
                            func_001F9D78(arg0, ((BtlObjXf_Update(arg0) ^ 0xD2) != 0) ? 0xFA : 0xF9);
                        } else {
                            *(s32 *)(arg0 + 0x8DC) = *(s32 *)(arg0 + 0x8DC) | 1;
                        }
                    } else if ((func_0023F420(arg0) & 0x1000) && (func_00211310(arg0, 1, 0x40000) == 0) &&
                               (func_00212820(arg0) != 0)) {
                        func_002113C0(arg0, 0xF, 1, 1);
                        if (BtlPad_Test4C(arg0, 0x18) != 0) {
                            *(s32 *)(arg0 + 0x8C4) = *(s32 *)(arg0 + 0x8C4) + 1;
                            /* cvt.w.s of (1 - ratio) * 10.0f, truncates toward zero-even. */
                            ratio = BtlMember_GetHealthRatio(arg0);
                            t = (1.0f - ratio) * 10.0f;
                            rounded = (s32)t;
                            if (*(s32 *)(arg0 + 0x8C4) >= rounded + 5) {
                                func_001F9D78(arg0, ((BtlObjXf_Update(arg0) ^ 0xD2) != 0) ? 0x1A7 : 0x1A6);
                                pos = BtlChar_GetPos(arg0);
                                *(f32 *)(pos + 0xC0) = *(f32 *)(pos + 0xC0) * 0.5f;
                                f21 = *(f32 *)(BtlChar_GetPos(arg0) + 0xC0);
                                func_0020FC38(arg0, 0x1F);
                            }
                        }
                    }
                    if ((D_00385FB8 < (f32)*(s32 *)(arg0 + 0x8CC)) && (func_00212820(arg0, 1) != 0)) {
                        if (BtlMember_HasKi(arg0, func_0023FB58(arg0, 1)) != 0) {
                            if (BtlPad_Test48(arg0, 0xC) != 0) {
                                func_002113C0(arg0, 1, 0x8000, 1);
                            } else if (BtlPad_Test48(arg0, 0xD) != 0) {
                                func_002113C0(arg0, 1, 0x4000, 1);
                            }
                        }
                    }
                    func_002113C0(arg0, 1, 0x1000, 1);
                    func_002113C0(arg0, 1, 0x02000000, 1);
                    func_00206958(arg0, (s64)0x8000 << 29);
                    if (*(s32 *)(arg0 + 0x8CC) > 0) {
                        func_00217238(arg0, func_00218838(arg0, 0));
                    }
                }
            }
        } else if (v >= 0xFD) {
            if ((v < 0x1A8) && (v >= 0x1A6)) {
                goto block_41;
            }
        } else {
block_41:
            func_001F9FB0(arg0, 0);
            f21 = 0.0f;
            func_002113C0(arg0, 0, 2, 1);
            f22 = D_00385FC0;
        }
    } else {
        func_001FA0A0(arg0, 0xFC, 0);
        f21 = 0.0f;
        f22 = D_00385FBC;
    }

    f20 = D_00385FC4;
    s0 = func_00218838(arg0, 0) != 0;
    func_00215068(D_00385FC8, f20, arg0, 5, 0xD);
    if (s0 != 0) {
        func_00215E88(f20, arg0, 3);
    } else {
        func_00215E88(f20, arg0, 5);
    }
    f20 = 0.0f;
    func_00216208(f21, f22, arg0);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 1, 0x800, 1);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 6, 8, 1);

    pos = BtlChar_GetPos(arg0);
    f21 = *(f32 *)(pos + 0xB0);
    v2 = BtlObjXf_Update(arg0);
    if (v2 < 0xFB) {
        if (v2 < 0xF9) {
            if ((v2 < 0xD4) && (v2 >= 0xD2)) {
                f20 = 1.0f;
            }
        } else {
            f20 = 1.0f - func_001FA318(arg0);
        }
    } else if ((v2 >= 0xFD) && (v2 < 0x1A8) && (v2 >= 0x1A6)) {
        f20 = 1.0f - func_001FA318(arg0);
    }
    pos = BtlChar_GetPos(arg0);
    *(f32 *)(pos + 0xD4) = f21 * f20;
}
