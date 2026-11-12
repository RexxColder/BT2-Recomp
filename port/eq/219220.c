#include "common.h"

extern s32 BtlObjXf_Update(s32 arg0);
extern void func_002188C8(s32 arg0);
extern s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
extern void func_0020FC38(s32 arg0, s32 arg1);
extern void BtlChar_SetVibration(s32 arg0, f32 farg0, f32 farg1);
extern s32 BtlPad_Test48(s32 arg0, s32 arg1);
extern s32 BtlPad_Test4C(s32 arg0, s32 arg1);
extern void func_001F9D78(s32 arg0, s32 arg1);
extern void func_002182A8(s32 arg0);
extern f32 func_001FA318(s32 arg0);
extern void func_001F9FB0(s32 arg0, s32 arg1);
extern s32 func_001FA2E0(s32 arg0);
extern s32 func_0023F2D8(s32 arg0);
extern void func_00212DD8(s32 arg0, s32 arg1);
extern u8 *BtlChar_GetPos(s32 arg0);
extern f32 func_0023F048(s32 arg0);
extern f32 func_001FA308(s32 arg0);
extern s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_00206958(s32 arg0, s64 arg1);
extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
extern void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
extern void func_00216208(f32 farg0, f32 farg1, s32 arg0);
extern void func_00216678(s32 arg0);
extern void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_00385B70;
extern f32 D_00385B74;
extern f32 D_00385B78;
extern f32 D_00385B7C;
extern f32 D_00385B80;

/* Per-frame step of a six-phase move chain (states 0x39, 0x56..0x67 in groups of three:
   start / hold-with-input / finish), then the shared movement and flag tail. */
void func_00219220(u8 *self) {
    s32 obj = (s32)self;
    f32 speed = D_00385B70;
    s32 state = BtlObjXf_Update(obj);
    f32 limit;

    switch (state) {
    case 0x39:
        func_001F9FB0(obj, 0);
        speed = 0.0f;
        func_002113C0(obj, 5, 0x800, 1);
        break;
    case 0x56: case 0x59: case 0x5C: case 0x5F: case 0x62: case 0x65:
        func_002188C8(obj);
        func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0);
        break;
    case 0x57: case 0x5A: case 0x5D: case 0x60: case 0x63: case 0x66:
        func_002188C8(obj);
        if (func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0)) {
            func_0020FC38(obj, 0x2F);
            BtlChar_SetVibration(obj, 1.0f, D_00385B74);
        } else {
            if (!BtlPad_Test48(obj, 0)) {
                func_001F9D78(obj, BtlObjXf_Update(obj) + 1);
            }
            if (BtlPad_Test4C(obj, 3) || BtlPad_Test4C(obj, 2) || BtlPad_Test4C(obj, 1)) {
                func_001F9D78(obj, 0x39);
                func_002182A8(obj);
                func_0020FC38(obj, 0x1F);
                *(s32 *)(self + 0x14A0) = *(s32 *)(self + 0x14A0) + 1;
            }
        }
        *(f32 *)(self + 0x9B0) = func_001FA318(obj);
        func_00206958(obj, 0x40000);
        break;
    case 0x58: case 0x5B: case 0x5E: case 0x61: case 0x64: case 0x67:
        func_001F9FB0(obj, 0);
        if (func_001FA2E0(obj)) {
            func_00212DD8(obj, func_0023F2D8(obj));
            if (BtlObjXf_Update(obj) == 0x58 || BtlObjXf_Update(obj) == 0x5B) {
                u8 *pos = BtlChar_GetPos(obj);
                *(f32 *)(pos + 0xC0) = func_0023F048(obj);
            }
        }
        speed = 0.0f;
        limit = func_001FA308(obj) - 15.0f;
        if (limit < (f32)BtlObjAnim_QueryEvent(*(s32 *)(self + 0x1530), 2, 0, 1)) {
            func_00206958(obj, 0x40000);
        }
        break;
    default:
        break;
    }

    if (!func_00211310(obj, 5, 4)) {
        speed = 0.0f;
    }
    func_00215068(obj, 5, 12, D_00385B78, 0.5f);
    func_00215E88(D_00385B7C, obj, 2);
    func_00216208(speed, D_00385B80, obj);
    func_00216678(obj);
    func_002113C0(obj, 9, 0x200, 1);
    func_002113C0(obj, 15, 0x40, 1);
    if (func_00211310(obj, 0, 0x100)) {
        func_002113C0(obj, 0, 2, 1);
    }
}
