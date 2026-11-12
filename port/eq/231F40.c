#include "common.h"

/* 0x00231F40: per-frame state handler of a battle character: runs the action state (BtlObjXf_Update id, three
 * character variants 284..287/290, 318..321/324, 352..355/358, plus 386), then applies the common per-frame
 * flag clears / motion setup, and finally maps the pad direction mask to a state flag. */
u32 func_00212320(u8 *o);
extern s32 BtlObjXf_Update();
s32 func_00211310(u8 *o, s32 a, s32 b);
f32 func_001FA340(u8 *o);
void func_001FA360(u8 *o, f32 f);
s32 func_001FA0A0(u8 *o, s32 a, s32 b);
void func_001FA110(u8 *o, s32 a);
void BtlChar_SetVibration(u8 *o, f32 a, f32 b);
s32 BtlPad_Test48(u8 *o, s32 a);
s32 func_001F9D78(u8 *o, s32 a);
f32 func_00241AE8(u8 *o, s32 a);
s32 func_00241778(u8 *o, s32 a);
s32 func_00203310(u8 *o, s32 a, s32 b);
s32 func_002113C0(u8 *o, s32 a, s32 b, s32 c);
f32 func_001FA308(u8 *o);
s32 BtlObjAnim_QueryEvent(u8 *a, s32 b, s32 c, s32 d);
s32 func_00241170(u8 *o, s32 a);
void func_00230D30(u8 *o, s32 a, s32 b);
void func_002310B8(u8 *o, s32 a, s32 b);
s32 func_001F9FB0(u8 *o, s32 a);
void func_001FCD80(u8 *o);
s32 func_001FA2E0(u8 *o);
void func_00230C48(u8 *o, s32 a);
void func_00230C60(u8 *o, s32 a);
void func_002171C0(u8 *o, f32 a, f32 b);
s32 func_002411E0(u8 *o, s32 a);
void func_002177A8(u8 *o, s32 a, s32 b, s32 c);
void func_00215068(u8 *o, s32 a, s32 b, f32 f12, f32 f13);
void func_00215E88(u8 *o, s32 a, f32 f);
void func_00216208(u8 *o, f32 a, f32 b);
void func_00216678(u8 *o);
s32 func_00206958(u8 *o, s32 a);
s32 BtlPad_GetMask(u8 *o, s32 a);

extern f32 D_003868AC;
extern f32 D_003868B0;
extern f32 D_003868B4;
extern f32 D_003868B8;
extern f32 D_003868BC;
extern f32 D_003868C0;
extern f32 D_003868C4;
extern f32 D_003868C8;
extern f32 D_003868CC;
extern f32 D_003868D0;

s32 func_00231F40(u8 *obj) {
    s32 *cnt = (s32 *)(obj + 0x8C0);
    s32 *cnt2 = (s32 *)(obj + 0x8C4);
    s32 moving = 0;
    s32 padFlag = 0;
    s32 base = 1;
    s32 chr;
    s32 state;
    s32 result;
    s32 mask;
    f32 f;
    f32 *prog;

    chr = (s32)func_00212320(obj);
    state = BtlObjXf_Update(obj);

    switch (state) {
    case 284:
    case 318:
    case 352:
        if (func_00211310(obj, 7, 0x20000)) {
            f = func_001FA340(obj);
            if (30.0f < f) {
                func_001FA360(obj, f / 30.0f + f / 30.0f);
            }
        }
        moving = 1;
        func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0);
        padFlag = 1;
        break;
    case 285:
    case 319:
    case 353:
        func_001FA110(obj, 0);
        BtlChar_SetVibration(obj, D_003868AC, D_003868B0);
        *cnt2 = *cnt2 + 1;
        if (BtlPad_Test48(obj, 1)) {
            prog = (f32 *)(obj + 0xA30);
            f = *prog + 1.0f / (func_00241AE8(obj, chr) * 30.0f);
            *prog = f;
            if (1.0f < f) {
                *prog = 1.0f;
                func_001F9D78(obj, BtlObjXf_Update(obj) + 1);
            }
            moving = 1;
        } else {
            func_001F9D78(obj, BtlObjXf_Update(obj) + 1);
            moving = 1;
        }
        padFlag = 1;
        break;
    case 286:
    case 320:
    case 354:
        if (func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0)) {
            if (func_00203310(obj, func_00241778(obj, chr), 0x2F)) {
                func_002113C0(obj, 6, 4, 1);
            }
        }
        moving = 1;
        f = func_001FA308(obj);
        if (!(f < (f32)BtlObjAnim_QueryEvent(*(u8 **)(obj + 0x1530), 0x400, 0, 0))) {
            moving = func_00241170(obj, chr) != 0;
        }
        func_00230D30(obj, chr, 0);
        func_002310B8(obj, chr, 0);
        break;
    case 287:
    case 321:
    case 355:
        func_001FA110(obj, 0);
        func_00230D30(obj, chr, 1);
        func_002310B8(obj, chr, 1);
        moving = func_00241170(obj, chr) != 0;
        *cnt = *cnt + 1;
        if (*cnt >= 0x97) {
            func_002113C0(obj, 7, 2, 1);
        }
        if (func_00211310(obj, 7, 2)) {
            func_001F9D78(obj, BtlObjXf_Update(obj) + 3);
            *cnt = 0;
        }
        break;
    case 290:
    case 324:
    case 358:
        func_001F9FB0(obj, 0);
        break;
    case 386:
        if (func_001FA0A0(obj, 0x160, 0)) {
            func_001FCD80(obj);
        }
        if (func_001FA2E0(obj)) {
            func_00230C48(obj, 0);
        }
        func_00230C60(obj, 0);
        base = 0;
        func_002113C0(obj, 9, 4, 1);
        padFlag = 1;
        break;
    default:
        break;
    }

    if (moving) {
        if (!BtlPad_Test48(obj, 8)) {
            func_002113C0(obj, 7, 0x100000, 1);
        }
        if (func_00211310(obj, 7, 0x100000)) {
            func_002171C0(obj, D_003868B4, D_003868B8);
        }
    }
    if (base && (func_002411E0(obj, chr) & 0x400000) == 0) {
        s32 a = BtlObjXf_Update(obj) + 7;
        func_002177A8(obj, a, BtlObjXf_Update(obj) + 14, moving);
    }
    if (moving) {
        f = D_003868BC;
        func_00215068(obj, 3, 12, D_003868C0, f);
        func_00215E88(obj, 2, f);
        func_00216208(obj, 0.0f, D_003868C4);
    } else {
        f = D_003868C8;
        func_00215068(obj, 5, 12, D_003868CC, f);
        func_00215E88(obj, 6, f);
        func_00216208(obj, 0.0f, D_003868D0);
    }
    func_00216678(obj);
    func_002113C0(obj, 9, 0x200, 1);
    func_002113C0(obj, 13, 8, 1);
    func_002113C0(obj, 13, 1, 1);
    func_002113C0(obj, 13, 0x10, 1);
    if ((func_002411E0(obj, chr) & 0x10) == 0) {
        func_00206958(obj, 0x8000);
    }
    func_002113C0(obj, 15, 0x40, 1);
    func_002113C0(obj, 9, 0x40000, 1);
    func_002113C0(obj, 1, 0x800000, 1);
    result = func_00211310(obj, 0, 2);
    if (!result) {
        result = func_00211310(obj, 0, 4);
        if (!result) {
            result = func_002113C0(obj, 0, 2, 1);
        }
    }
    if (padFlag) {
        mask = BtlPad_GetMask(obj, 1);
        if (mask == 0x2000) {
            return func_002113C0(obj, 15, 0x8000, 1);
        } else if (mask > 0x2000) {
            result = 0x8000;
            if (mask == 0x4000) {
                return func_002113C0(obj, 15, 0x10000, 1);
            } else if (mask == 0x8000) {
                return func_002113C0(obj, 15, 0x40000, 1);
            }
        } else {
            result = 0x1000;
            if (mask == 0x1000) {
                return func_002113C0(obj, 15, 0x20000, 1);
            }
        }
    }
    return result;
}
