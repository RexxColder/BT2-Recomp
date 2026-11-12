#include "common.h"

#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define S32(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern f32 D_00386800;
extern f32 D_00386804;
extern f32 D_00386808;
extern f32 D_0038680C;
extern f32 D_00386810;
extern f32 D_00386814;
extern f32 D_00386818;

s32 func_00212320(u8 *a0);
s32 func_001FA110(u8 *a0, s32 a1);
s32 BtlObjXf_Update(u8 *a0);
s32 func_002411E0(u8 *a0, s32 a1);
void func_002177A8(u8 *a0, s32 a1, s32 a2, s32 a3);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 f12, f32 f13);
void func_00215E88(u8 *a0, s32 a1, f32 f12);
void func_00216208(u8 *a0, f32 f12, f32 f13);
void func_00216678(u8 *a0);
void func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
void func_00206958(u8 *a0, s64 a1);
void func_001FBE80(u8 *a0, f32 f12, f32 f13);
void BtlChar_Vibrate(u8 *a0, f32 f12, f32 f13);
u8 *BtlChar_GetPos(u8 *a0);
f32 sinf(f32 x);
f32 cosf(f32 x);
void func_00312680(void *a0, void *a1, f32 f12);
void func_0026A2B0(s32 a0, f32 f12, void *a1);
s32 func_00211310(u8 *a0, s32 a1, s32 a2);
s32 BtlPad_Test4C(u8 *a0, s32 a1);
void func_00212DD8(u8 *a0, s32 a1);
void func_00203888(u8 *a0, s32 a1, s32 a2);
s32 BtlMember_IsKiEmpty(u8 *a0);
f32 func_00217E58(u8 *a0);
s32 func_00217488(u8 *a0);
u8 *BtlMember_GetActiveGauge(u8 *a0);

void func_0022FFC8(u8 *arg0, s32 arg1) {
    u8 sp[0x10];
    s32 s0;
    s32 s2;
    s32 s3;
    s32 v1;
    f32 f20;
    f32 f21;
    f32 f0;
    f32 f1;
    u8 *p;
    u8 *g1;
    u8 *g2;

    s2 = -1;
    s0 = -1;
    s3 = func_00212320(arg0);
    func_001FA110(arg0, 0);
    v1 = BtlObjXf_Update(arg0);

    switch (v1) {
    case 0x141:
        s2 = 0x148;
        s0 = 0x14F;
        break;
    case 0x11F:
        s2 = 0x126;
        s0 = 0x12D;
        break;
    case 0x163:
        s2 = 0x16A;
        s0 = 0x171;
        break;
    case 0x183:
        s2 = 0x185;
        s0 = 0x187;
        break;
    default:
        break;
    }

    if (s2 >= 0 && s0 >= 0) {
        if ((func_002411E0(arg0, s3) & 0x400000) == 0) {
            func_002177A8(arg0, s2, s0, 1);
        }
    }

    f20 = D_00386800;
    func_00215068(arg0, 5, 0xC, D_00386804, f20);
    f21 = 0.0f;
    func_00215E88(arg0, 6, f20);
    func_00216208(arg0, f21, D_00386808);
    f20 = D_0038680C;
    func_00216678(arg0);
    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xD, 1, 1);
    func_002113C0(arg0, 0xD, 0x10, 1);
    func_002113C0(arg0, 9, 0x200000, 1);
    func_00206958(arg0, 0x8000);
    func_001FBE80(arg0, 5.0f, f20);
    BtlChar_Vibrate(arg0, 1.0f, f20);
    func_002113C0(arg0, 9, 0x1000, 1);
    func_002113C0(arg0, 3, 0xF, 1);
    func_002113C0(arg0, 0xF, 0x100000, 1);

    p = BtlChar_GetPos(arg0);
    f0 = -sinf(F32(p, 0x14));
    F32(sp, 0x4) = f21;
    F32(sp, 0x0) = f0;
    p = BtlChar_GetPos(arg0);
    f0 = -cosf(F32(p, 0x14));
    F32(sp, 0x8) = f0;
    func_00312680(sp, sp, 0.5f);
    func_0026A2B0(S32(arg0, 0x1530), 4.0f, sp);

    /* block on 0x183 family of bits: function 0x211310 (7, 0x40000) */
    if (func_00211310(arg0, 7, 0x40000) != 0) {
        func_00203888(arg0, 0x190, 1);
        if (BtlMember_IsKiEmpty(arg0) != 0) {
            func_002113C0(arg0, 7, 0x40000, 0);
            func_002113C0(arg0, 0, 0x4000, 1);
        }
    } else {
        if (func_00211310(arg0, 0, 0x4000) == 0) {
            if (BtlPad_Test4C(arg0, 7) != 0) {
                func_002113C0(arg0, 7, 0x40000, 1);
                func_00212DD8(arg0, 0x17);
            }
        }
    }

    /* L2302C8 */
    f0 = func_00217E58(arg0);
    F32(arg0, 0xA38) = f0;
    if (func_00217488(arg0) == 0xE2) {
        F32(arg0, 0xA38) = F32(arg0, 0xA38) * D_00386810;
    }

    /* L302F8 */
    if (func_00211310(arg0, 7, 0x40000) != 0) {
        g1 = BtlMember_GetActiveGauge(arg0);
        g2 = BtlMember_GetActiveGauge(arg0);
        f0 = (f32)S32(g1, 0xC);
        f1 = (f32)S32(g2, 0x10);
        f1 = F32(arg0, 0xA38) * (f0 / f1 * 0.5f + D_00386814);
        F32(arg0, 0xA38) = f1;
    } else {
        if (func_00211310(arg0, 0, 0x4000) != 0) {
            F32(arg0, 0xA38) = F32(arg0, 0xA38) * D_00386818;
        }
    }

    /* L30388 */
    if (func_00211310(arg0, 7, 0x800) != 0) {
        func_002113C0(arg0, 7, 0x40000, 0);
    } else {
        func_002113C0(arg0, 0xF, 0x10, 1);
    }
}
