#include "common.h"

#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define S32(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern f32 D_00385E04;
extern f32 D_00385E08;
extern f32 D_00385E0C;
extern f32 D_00385E10;
extern f32 D_00385E14;
extern f32 D_00385E18;
extern f32 D_00385E1C;
extern f32 D_00385E20;
extern f32 D_00385E24;

f32 func_00240D50(u8 *a0, s32 a1);
s32 BtlObjXf_Update(u8 *a0);
s32 func_001FA0A0(u8 *a0, s32 a1, s32 a2);
void func_00206958(u8 *a0, s64 a1);
s32 BtlPad_Test48(u8 *a0, s32 a1);
void func_001F9D78(u8 *a0, s32 a1);
f32 func_001FA318(u8 *a0);
void BtlChar_SetVibration(u8 *a0, f32 f12, f32 f13);
s32 func_00211310(u8 *a0, s32 a1, s32 a2);
s32 func_00211328(u8 *a0, s32 a1, s32 a2);
void func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
void func_001F9FB0(u8 *a0, s32 a1);
void func_001FA380(u8 *a0, f32 f12);
u8 *BtlChar_GetPos(u8 *a0);
void BtlOpp_GetDelta(u8 *a0, void *a1);
f32 BtlOpp_GetHalfHeightDiff(u8 *a0);
f32 BtlMove_CalcVerticalSpeed(f32 f12, f32 f13);
s32 func_00217BD0(u8 *a0);
f32 func_001FA308(u8 *a0);
s32 BtlObjAnim_QueryEvent(s32 a0, s32 a1, s32 a2, s32 a3);
void func_00215550(u8 *a0, s32 a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 f12, f32 f13);
void func_00215E88(u8 *a0, s32 a1, f32 f12);
void func_00216208(u8 *a0, f32 f12, f32 f13);
void func_00216678(u8 *a0);

void func_0021DA88(u8 *arg0) {
    u8 sp[0x10];
    s32 v1;
    s32 x;
    s32 v;
    s32 r;
    s32 s1;
    u8 *p;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f0;

    s1 = 1;
    f21 = func_00240D50(arg0, 6);
    v1 = BtlObjXf_Update(arg0);
    f22 = f21;
    f23 = D_00385E04;

    if (v1 == 0x54) {
        /* DB38 */
        x = BtlObjXf_Update(arg0);
        v = func_001FA0A0(arg0, x + 1, 0);
        if (v != 0) {
            BtlChar_SetVibration(arg0, 1.0f, D_00385E08);
        } else {
            v = BtlPad_Test48(arg0, 1);
            if (v != 0) {
                /* DBA8 */
                r = func_00211310(arg0, 0, 1);
                if (r == 0) {
                    x = BtlObjXf_Update(arg0);
                    func_001F9D78(arg0, x + 1);
                }
            } else {
                x = BtlObjXf_Update(arg0);
                func_001F9D78(arg0, x + 1);
            }
        }
        /* DBD0 */
        f0 = func_001FA318(arg0);
        F32(arg0, 0x9B0) = f0;
        func_00206958(arg0, 0x40000);
        func_00206958(arg0, 0x8);
        func_00206958(arg0, 0x8);
        func_00206958(arg0, 0x400);
        BtlChar_SetVibration(arg0, D_00385E0C, D_00385E10);
        /* DC20 */
        func_002113C0(arg0, 7, 0x80000, 1);
    } else if (v1 < 0x55) {
        if (v1 == 0x53) {
            /* DB08 */
            func_001FA0A0(arg0, 0x54, 0);
            func_00206958(arg0, 0x8);
            func_00206958(arg0, 0x400);
            /* DC20 */
            func_002113C0(arg0, 7, 0x80000, 1);
        }
    } else {
        if (v1 == 0x55) {
            /* DC38 */
            func_001F9FB0(arg0, 0);
            func_001FA380(arg0, 2.0f);
            if (func_00211310(arg0, 4, 2) != 0) {
                f21 = 0.0f;
                p = BtlChar_GetPos(arg0);
                F32(p, 0xC0) = f21;
                if (func_00211328(arg0, 4, 2) == 0) {
                    BtlOpp_GetDelta(arg0, sp);
                    f0 = BtlOpp_GetHalfHeightDiff(arg0);
                    f20 = BtlMove_CalcVerticalSpeed(F32(sp, 0x4) + f0, f21);
                    p = BtlChar_GetPos(arg0);
                    F32(p, 0xC4) = f20;
                }
            }
            /* DCC8 */
            if (func_00211310(arg0, 4, 0xC) != 0) {
                f21 = 0.0f;
                f23 = D_00385E14;
                s1 = 0;
                if (func_00217BD0(arg0) != 0) {
                    p = BtlChar_GetPos(arg0);
                    F32(p, 0xC0) = f21;
                }
            }
            /* DD04 */
            f0 = func_001FA308(arg0);
            f20 = f0 - 15.0f;
            r = BtlObjAnim_QueryEvent(S32(arg0, 0x1530), 2, 0, 1);
            f0 = (f32)r;
            if (f20 < f0) {
                func_00206958(arg0, 0x40000);
            }
        }
    }

    /* DD4C / DD50 */
    r = func_00211310(arg0, 0, 1);
    if (r != 0 && s1 != 0) {
        f0 = (f32)S32(arg0, 0x8CC);
        f0 = f0 * 3.0f;
        f0 = f0 / 30.0f;
        f0 = 1.0f - f0;
        if (f0 < 0.0f) {
            f0 = 0.0f;
        }
        func_00215550(arg0, 1, f22, D_00385E20, D_00385E20, f0 * D_00385E1C, f0 * D_00385E18, D_00385E18, 1.0f); /* f17 = D_00385E18 and f18 = 1.0f are live in the asm */
    } else {
        func_00215068(arg0, 5, 0xD, D_00385E24, 1.0f);
    }

    /* DDFC */
    func_00215E88(arg0, 3, 1.0f);
    func_00216208(arg0, f21, f23);
    func_00216678(arg0);
    func_002113C0(arg0, 5, 0x40, 1);
    func_002113C0(arg0, 1, 0x2000, 1);
    func_002113C0(arg0, 9, 0x200, 1);
    func_00206958(arg0, (s64)0x8000 << 28);
    func_002113C0(arg0, 1, 0x800000, 1);
}
