#include "common.h"

extern f32 D_00385DA8;
extern f32 D_00385DAC;
extern f32 D_00385DB0;
extern f32 D_00385DB4;
extern f32 D_00385DB8;

s32 BtlObjXf_Update(void *arg0);
void func_002188C8(void *arg0);
s32 func_001FA0A0(void *arg0, s32 arg1, s32 arg2);
void BtlChar_SetVibration(void *arg0, f32 farg0, f32 farg1);
s32 BtlPad_Test48(void *arg0, s32 arg1);
s32 BtlPad_Test4C(void *arg0, s32 arg1);
s32 func_001F9D78(void *arg0, s32 arg1);
void func_002182A8(void *arg0);
void func_0020FC38(void *arg0, s32 arg1);
f32 func_001FA318(void *arg0);
s32 func_001F9FB0(void *arg0, s32 arg1);
s32 func_001FA2E0(void *arg0);
f32 func_001FA308(void *arg0);
s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00206958(void *arg0, s64 arg1);
s32 func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
void func_00215068(void *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(void *arg0, s32 arg1, f32 farg0);
void func_00216208(void *arg0, f32 farg0, f32 farg1);
void func_00216678(void *arg0);

void func_0021CEE8(void *arg0) {
    u8 *s0;
    s32 v;
    s32 v0;
    f32 f0;
    f32 f20;
    f32 f21;

    s0 = (u8 *)arg0;
    v = BtlObjXf_Update(s0);
    f21 = D_00385DA8;
    if (v == 0x9C) {
        goto l_50;
    }
    if (v < 0x9D) {
        if (v == 0x39) {
            goto l_c0;
        }
        goto l_e4;
    }
    if (v == 0x9D) {
        goto l_70;
    }
    if (v == 0x9E) {
        goto l_48;
    }
    goto l_e4;

l_50:
    func_002188C8(s0);
    func_001FA0A0(s0, 0x9D, 1);
    goto l_e4;

l_70:
    func_002188C8(s0);
    v0 = func_001FA0A0(s0, 0x9E, 0);
    if (v0 != 0) {
        BtlChar_SetVibration(s0, 1.0f, D_00385DAC);
        goto l_d030;
    }

    /* l_cfb0 */
    v0 = BtlPad_Test48(s0, 1);
    if (v0 == 0) {
        func_001F9D78(s0, 0x9E);
    }
    v0 = BtlPad_Test4C(s0, 3);
    if (v0 != 0) {
        goto l_d008;
    }
    v0 = BtlPad_Test4C(s0, 2);
    if (v0 != 0) {
        goto l_d008;
    }
    v0 = BtlPad_Test4C(s0, 0);
    if (v0 == 0) {
        goto l_d030;
    }

l_d008:
    func_001F9D78(s0, 0x39);
    func_002182A8(s0);
    func_0020FC38(s0, 0x1F);
    *(s32 *)(s0 + 0x14A0) = *(s32 *)(s0 + 0x14A0) + 1;

l_d030:
    f0 = func_001FA318(s0);
    *(f32 *)(s0 + 0x9B0) = f0;
    func_00206958(s0, 0x40000);
    goto l_e4;

l_48:
    func_001F9FB0(s0, 0);
    v0 = func_001FA2E0(s0);
    if (v0 != 0) {
        func_0020FC38(s0, 0x4B);
    }
    f21 = 0.0f;
    f0 = func_001FA308(s0);
    f20 = f0 - 15.0f;
    v0 = BtlObjAnim_QueryEvent(*(s32 *)(s0 + 0x1530), 2, 0, 1);
    if (f20 < (f32)v0) {
        func_00206958(s0, 0x40000);
    }
    goto l_e4;

l_c0:
    func_001F9FB0(s0, 0);
    f21 = 0.0f;
    func_002113C0(s0, 5, 0x800, 1);

l_e4:
    v0 = func_00211310(s0, 5, 4);
    if (v0 == 0) {
        f21 = 0.0f;
    }
    func_00215068(s0, 5, 0xC, D_00385DB0, 0.5f);
    func_00215E88(s0, 2, D_00385DB4);
    func_00216208(s0, f21, D_00385DB8);
    func_00216678(s0);
    func_002113C0(s0, 9, 0x200, 1);
    func_002113C0(s0, 0xF, 0x40, 1);
    v0 = func_00211310(s0, 0, 0x100);
    if (v0 == 0) {
        return;
    }
    func_002113C0(s0, 0, 2, 1);
}
