#include "common.h"

#define F32AT(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define S32AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTRAT(p, o) (*(u8 **)((u8 *)(p) + (o)))
#define S64AT(p, o) (*(s64 *)((u8 *)(p) + (o)))

s32 BtlObjXf_Update(void *arg0);
void func_001FA110(void *, s32);
void func_001FA360(f32, void *);
s32 func_001FA0A0(void *, s32, s32);
void BtlAnim_SetBlend(f32, void *);
s32 func_0023F410(void *);
void func_0020FC38(void *, s32);
void BtlChar_Vibrate(f32, f32, void *);
void func_002113C0(void *, s32, s32, s32);
void BtlMove_BrakeVertical(void *);
void func_001F9FB0(void *, s32);
void func_00216678(void *);
s32 func_00211310(void *, s32, s32);
f32 func_00240D50(void *, s32);
void func_00216890(f32, f32, void *);
void func_00206958(void *, s64);
void BtlChar_SetVibration(f32, f32, void *);
s32 BtlPad_Test4C(void *, s32);
s32 BtlPad_Test48(void *, s32);
s32 EftWater_GetSurfaceY(void *, s32, s32);
f32 func_00217360(void *);
s32 func_00240EA8(void *, s32);
s32 func_00203888(void *, s32, s32);
void func_001F9D78(void *, s32);
void func_00215068(f32, f32, void *, s32, s32);
void func_00215E88(f32, void *, s32);
void func_00216208(f32, f32, void *);
extern f32 D_00386610;
extern f32 D_00386614;
extern f32 D_00386618;
extern f32 D_0038661C;
extern f32 D_00386620;
extern f32 D_00386624;
extern f32 D_00386628;
extern f32 D_0038662C;
extern f32 D_00386630;
extern f32 D_00386634;
extern f32 D_00386638;

void func_0022CA10(void *arg0) {
    u8 sp[0x20];
    s32 v;
    s32 s2;
    s32 t;
    u8 *v1;
    f32 f20;

    v = BtlObjXf_Update(arg0);
    if (v == 0x3E) {
        /* case 0x3E */
        func_001FA110(arg0, 0);
        s2 = 0;
        func_00216890(func_00240D50(arg0, 9), D_00386620, arg0);
        func_00206958(arg0, 8);
        func_00206958(arg0, (s64)0x8000 << 28);
        func_002113C0(arg0, 1, 0x2000, 1);
        BtlChar_SetVibration(D_00386624, D_00386628, arg0);
        if (BtlPad_Test4C(arg0, 3) != 0) {
            s2 = 1;
            if (func_00211310(arg0, 1, 1) == 0 && BtlPad_Test48(arg0, 7) != 0) {
                S32AT(arg0, 0x8DC) = S32AT(arg0, 0x8DC) | 1;
            }
        }
        v1 = PTRAT(arg0, 0x1530);
        if ((S64AT(v1, 0xE80) & (s64)0x41000000) != (s64)0x40000000) {
            f20 = 10.0f;
            if (EftWater_GetSurfaceY(sp, 0x40000000, 0x20) != 0 &&
                *(f32 *)sp < F32AT(PTRAT(arg0, 0x1530), 0xE64)) {
                f20 = 3.0f;
            }
            if (func_00217360(arg0) < f20) {
                s2 = 1;
                func_002113C0(arg0, 0, 2, 0);
            }
        }
        if (func_00211310(arg0, 0, 0x20) != 0) {
            s2 = 1;
        }
        t = func_00240EA8(arg0, 2);
        t = func_00203888(arg0, t, 0);
        if (t != 0) {
            s2 = 1;
        }
        if (s2 != 0) {
            func_001F9D78(arg0, 0x3F);
            BtlAnim_SetBlend(D_0038662C, arg0);
        }
        func_002113C0(arg0, 0xD, 8, 1);
    } else if (v == 0x3D) {
        /* case 0x3D */
        if (S32AT(arg0, 0x8DC) & 2) {
            func_001FA360(D_00386610, arg0);
        }
        if (func_001FA0A0(arg0, 0x3E, 0) != 0) {
            BtlAnim_SetBlend(D_00386614, arg0);
            if (func_0023F410(arg0) & 0x10) {
                func_0020FC38(arg0, 0x1D);
            } else {
                func_0020FC38(arg0, 0x1C);
            }
            BtlChar_Vibrate(D_00386618, D_0038661C, arg0);
            func_002113C0(arg0, 0xE, 0x200, 1);
        }
        BtlMove_BrakeVertical(arg0);
    } else if (v == 0x3F) {
        /* case 0x3F */
        func_001F9FB0(arg0, 0);
        func_00216678(arg0);
        if (func_00211310(arg0, 0, 4) != 0) {
            func_002113C0(arg0, 0, 2, 0);
        }
    }

    /* common tail (CCF0) */
    f20 = D_00386630;
    func_00215068(D_00386634, f20, arg0, 5, 0xC);
    func_00215E88(f20, arg0, 6);
    func_00216208(0.0f, D_00386638, arg0);
    func_002113C0(arg0, 1, 0x800000, 1);
    func_002113C0(arg0, 8, 4, 1);
}
