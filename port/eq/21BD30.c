#include "common.h"

void *BtlChar_GetPos(void *a0);
void BtlChar_SetVibration(void *a0, f32 f12, f32 f13);
s32 BtlObjAnim_QueryEvent(s32 a0, s32 a1, s32 a2, s32 a3);
s32 BtlObjXf_Update(void *a0);
s32 BtlPad_Test48(void *a0, s32 a1);
s32 BtlPad_Test4C(void *a0, s32 a1);
void func_001F9D78(void *a0, s32 a1);
void func_001F9FB0(void *a0, s32 a1);
s32 func_001FA0A0(void *a0, s32 a1, s32 a2);
f32 func_001FA308(void *a0);
f32 func_001FA318(void *a0);
void func_00206958(void *a0, s64 a1);
void func_0020FC38(void *a0, s32 a1);
s32 func_00211310(void *a0, s32 a1, s32 a2);
s32 func_002113C0(void *a0, s32 a1, s32 a2, s32 a3);
void func_00215068(void *a0, s32 a1, s32 a2, f32 f12, f32 f13);
/* GUESS arity: 2 int args + 7 float args (f12..f18) as the asm passes them */
void func_00215550(void *a0, s32 a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18);
void func_00215E88(void *a0, s32 a1, f32 f12);
void func_00216208(void *a0, f32 f12, f32 f13);
void func_00216678(void *a0);
s32 func_00217BD0(void *a0);
void func_002182A8(void *a0);
f32 func_00240D50(void *a0, s32 a1);
f32 func_00240ED8(void *a0, s32 a1);
f32 func_00240F18(void *a0, s32 a1);

extern f32 D_00385CD8 __attribute__((section(".data")));
extern f32 D_00385CDC __attribute__((section(".data")));
extern f32 D_00385CE0 __attribute__((section(".data")));
extern f32 D_00385CE4 __attribute__((section(".data")));
extern f32 D_00385CE8 __attribute__((section(".data")));
extern f32 D_00385CEC __attribute__((section(".data")));
extern f32 D_00385CF0 __attribute__((section(".data")));
extern f32 D_00385CF4 __attribute__((section(".data")));
extern f32 D_00385CF8 __attribute__((section(".data")));

void func_0021BD30(void *arg0) {
    s32 var_s1 = 1;
    s32 a1;
    f32 var_f21;
    f32 temp_f22;
    f32 temp_f20;
    f32 temp_f15;
    s32 v;

    if (func_00211310(arg0, 0, 0x100) != 0) {
        a1 = 5;
    } else {
        a1 = 4;
    }
    var_f21 = func_00240D50(arg0, a1);
    temp_f22 = var_f21;
    v = BtlObjXf_Update(arg0);

    switch (v) {
    case 0x77:
        func_001FA0A0(arg0, 0x78, 0);
        func_00206958(arg0, 0x1000);
        break;
    case 0x78:
        if (func_001FA0A0(arg0, 0x79, 0) != 0) {
            func_0020FC38(arg0, 0x2F);
            BtlChar_SetVibration(arg0, 1.0f, D_00385CD8);
        } else {
            if (BtlPad_Test48(arg0, 0) == 0) {
                func_001F9D78(arg0, 0x79);
            }
            if ((BtlPad_Test4C(arg0, 3) != 0) || (BtlPad_Test4C(arg0, 2) != 0) || (BtlPad_Test4C(arg0, 1) != 0)) {
                func_001F9D78(arg0, 0x39);
                func_002182A8(arg0);
                func_0020FC38(arg0, 0x1F);
                *(s32 *)((u8 *)arg0 + 0x14A0) = *(s32 *)((u8 *)arg0 + 0x14A0) + 1;
            }
        }
        *(f32 *)((u8 *)arg0 + 0x9B0) = func_001FA318(arg0);
        func_00206958(arg0, 0x40000);
        func_00206958(arg0, 0x1000);
        break;
    case 0x79:
        func_001F9FB0(arg0, 0);
        if (func_00211310(arg0, 4, 2) == 0) {
            if (func_00211310(arg0, 4, 0xC) != 0) {
                var_f21 = 0.0f;
                var_s1 = 0;
                if (func_00217BD0(arg0) != 0) {
                    *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xC0) = 0.0f;
                }
            } else {
                func_00206958(arg0, 0x1000);
            }
        } else {
            var_f21 = 0.0f;
            *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xC0) = 0.0f;
        }
        temp_f20 = func_001FA308(arg0) - 15.0f;
        if (temp_f20 < (f32)BtlObjAnim_QueryEvent(*(s32 *)((u8 *)arg0 + 0x1530), 2, 0, 1)) {
            func_00206958(arg0, 0x40000);
        }
        break;
    case 0x39:
        func_001F9FB0(arg0, 0);
        var_f21 = 0.0f;
        func_002113C0(arg0, 5, 0x800, 1);
        if (func_00217BD0(arg0) != 0) {
            *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xC0) = 0.0f;
        }
        break;
    default:
        break;
    }

    if (var_s1 != 0) {
        if (func_00211310(arg0, 0, 1) != 0) {
            temp_f20 = func_00240ED8(arg0, 0);
            temp_f15 = func_00240F18(arg0, 0);
            func_00215550(arg0, 1, temp_f22, temp_f20, 0.0f, temp_f15, 0.0f, D_00385CDC, D_00385CE0);
        } else {
            func_00215068(arg0, 5, 0xC, D_00385CE4, D_00385CE8);
        }
    } else {
        func_00215068(arg0, 5, 0xD, D_00385CEC, D_00385CF0);
    }
    func_00215E88(arg0, 3, D_00385CF4);
    func_00216208(arg0, var_f21, D_00385CF8);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 0xF, 0x40, 1);
    func_00206958(arg0, (s64)0x8000 << 28);
    func_002113C0(arg0, 1, 0x800000, 1);
}
