#include "common.h"

extern f32 func_001FA318(s32 arg0);
extern s32 func_00218128(s32 arg0, s32 arg1);
extern void func_001FA360(s32 arg0, f32 farg0);
extern s32 BtlObjXf_Update(s32 arg0);
extern void func_001F9FB0(s32 arg0, s32 arg1);
extern f32 func_00240D50(s32 arg0, s32 arg1);
extern f32 func_001FA340(s32 arg0);
extern f32 func_001FA350(s32 arg0);
extern f32 func_002173E8(s32 obj, f32 fa, f32 fb, f32 fc);
extern void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
extern void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
extern void func_00216208(f32 farg0, f32 farg1, s32 arg0);
extern void func_00216678(s32 arg0);
extern void func_0020D7E8(s32 arg0, f32 farg0, f32 farg1);
extern void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00217488(s32 arg0);
extern u8 *BtlChar_GetPos(s32 arg0);
extern f32 sinf(f32 farg0);
extern u8 *BtlMember_GetActiveGauge(s32 arg0);
extern f32 D_00386648;
extern f32 D_0038664C;
extern f32 D_00386650;
extern f32 D_00386654;
extern f32 D_00386658;
extern f32 D_0038665C;
extern f32 D_00386660;
extern f32 D_00386664;
extern f32 D_00386668;
extern f32 D_0038666C;
extern f32 D_00386670;
extern f32 D_00386674;
extern f32 D_00386678;
extern f32 D_0038667C;

/* Per-frame step of a dash/sidestep state (0x28..0x2A, 0x34..0x36 via jump table): selects the
   two move floats, runs the shared movement calls, bobs the vertical offset by sin(angle) while
   anim 25/26 plays, and clears/sets flag bits. */
void func_0022D200(s32 obj) {
    f32 g = 0.0f;
    f32 f = 0.0f;
    f32 p = func_001FA318(obj);
    f32 h;
    f32 ratio;
    s32 n;

    if (func_00218128(obj, 2)) {
        func_001FA360(obj, D_00386648);
    }
    switch (BtlObjXf_Update(obj)) {
    case 0x28:
    case 0x34:
        func_001F9FB0(obj, 0);
        if (D_0038664C < p && p < D_00386650) {
            f = func_00240D50(obj, 11);
            g = D_00386654;
        } else {
            f = 0.0f;
            g = D_0038666C;
        }
        break;
    case 0x29:
    case 0x2A:
    case 0x35:
    case 0x36:
        func_001F9FB0(obj, 0);
        if (D_00386658 < p && p < D_0038665C) {
            p = func_00240D50(obj, 12);
            f = func_001FA340(obj);
            f = f / func_001FA350(obj);
            g = D_00386668;
            f = func_002173E8(obj, p, D_00386664, f * D_00386660);
        } else {
            f = 0.0f;
            g = D_0038666C;
        }
        break;
    default:
        break;
    }

    h = D_00386670;
    func_00215068(obj, 1, 12, D_00386674, h);
    func_00215E88(h, obj, 7);
    func_00216208(f, g, obj);
    func_00216678(obj);
    func_0020D7E8(obj, 5.0f, 10.0f);
    func_002113C0(obj, 5, 1, 1);
    func_002113C0(obj, 9, 0x200, 1);
    if (func_00211310(obj, 0, 1)) {
        n = func_00217488(obj);
        if (n < 27 && n >= 25) {
            p = func_001FA318(obj);
            if (p < h) {
                ratio = p / h;
            } else {
                ratio = 1.0f;
                if (!(p < D_00386678)) {
                    ratio = 1.0f - (p - D_00386678) / D_0038667C;
                }
            }
            h = sinf(*(f32 *)(BtlChar_GetPos(obj) + 0x24)) * 0.5f;
            *(f32 *)(BtlChar_GetPos(obj) + 0xD4) = h * ratio;
        }
    }
    if (func_00217488(obj) == 0x1A) {
        if (func_00211310(obj, 0, 4)) {
            func_002113C0(obj, 0, 2, 0);
        }
    }
    if (func_00211310(obj, 0, 0x100)) {
        func_002113C0(obj, 0, 2, 1);
    }
    if (BtlMember_GetActiveGauge(obj)[0x29]) {
        func_002113C0(obj, 6, 8, 1);
    }
}
