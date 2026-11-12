#include "common.h"

extern s32 func_00212320(s32 arg0);
extern s32 BtlObjXf_Update(s32 arg0);
extern s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_001FA2E0(s32 arg0);
extern void func_00230BB0(s32 arg0, s32 arg1);
extern void func_00230C48(s32 arg0);
extern void func_00230C60(s32 arg0, s32 arg1);
extern void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void BtlChar_Vibrate(s32 arg0, f32 farg0, f32 farg1);
extern void func_001FCD80(s32 arg0);
extern f32 func_001FA318(s32 arg0);
extern void func_001F9FB0(s32 arg0, s32 arg1);
extern f32 func_00241B90(s32 arg0, s32 arg1);
extern void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
extern void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
extern void func_00216208(f32 farg0, f32 farg1, s32 arg0);
extern void func_00216678(s32 arg0);
extern s32 func_002411E0(s32 arg0, s32 arg1);
extern void func_00206958(s32 arg0, s64 arg1);
extern void func_00231188(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_003869A0;
extern f32 D_003869A4;
extern f32 D_003869A8;
extern f32 D_003869AC;
extern f32 D_003869B0;
extern f32 D_003869B4;
extern f32 D_003869B8;
extern f32 D_003869BC;

/* Throw-style move step; the state switch (jump table: 284..286/290, +34, +68 and 386) runs the
   phase action (advance, hold, recover), then one of two movement setups (moving / idle) and
   the shared flag setters, ending in func_00231188. */
void func_002350E0(s32 obj) {
    s32 moving = 0;
    s32 s1 = func_00212320(obj);
    s32 state = BtlObjXf_Update(obj);
    f32 f20;
    f32 f21;

    switch (state) {
    case 386:
        func_001FA0A0(obj, 352, 0);
        if (func_001FA2E0(obj)) {
            func_00230C48(obj);
        }
        func_00230C60(obj, 0);
        func_002113C0(obj, 9, 4, 1);
        break;
    case 284:
    case 318:
    case 352:
        func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0);
        if (func_001FA2E0(obj)) {
            func_00230BB0(obj, s1);
        }
        func_00230C60(obj, 0);
        func_002113C0(obj, 9, 4, 1);
        break;
    case 285:
    case 319:
    case 353:
        func_001FA0A0(obj, BtlObjXf_Update(obj) + 1, 0);
        func_00230C60(obj, 0);
        func_002113C0(obj, 9, 4, 1);
        break;
    case 286:
    case 320:
    case 354:
        func_001FA0A0(obj, BtlObjXf_Update(obj) + 4, 0);
        if (func_001FA2E0(obj)) {
            BtlChar_Vibrate(obj, D_003869A0, D_003869A4);
            func_002113C0(obj, 14, 0x200, 1);
            func_001FCD80(obj);
        }
        func_002113C0(obj, 1, 0x2000, 1);
        moving = 1;
        if (func_001FA318(obj) > 0.5f) {
            func_002113C0(obj, 3, 0x200, 1);
            func_002113C0(obj, 7, 0x80000, 1);
        }
        break;
    case 290:
    case 324:
    case 358:
        func_001F9FB0(obj, 0);
        if (func_001FA318(obj) < 0.5f) {
            func_002113C0(obj, 3, 0x200, 1);
            func_002113C0(obj, 7, 0x80000, 1);
        }
        break;
    default:
        break;
    }

    if (moving) {
        f20 = D_003869A8;
        f21 = func_00241B90(obj, s1);
        func_00215068(obj, 1, 9, D_003869AC, f20);
        func_00215E88(f20, obj, 3);
        func_00216208(f21, D_003869B0, obj);
    } else {
        f20 = D_003869B4;
        func_00215068(obj, 5, 12, D_003869B8, f20);
        func_00215E88(f20, obj, 7);
        func_00216208(0.0f, D_003869BC, obj);
    }
    func_00216678(obj);
    func_002113C0(obj, 13, 8, 1);
    func_002113C0(obj, 13, 0x10, 1);
    func_002113C0(obj, 13, 1, 1);
    if (!(func_002411E0(obj, s1) & 0x10)) {
        func_00206958(obj, 0x8000);
    }
    func_002113C0(obj, 1, 0x800000, 1);
    func_00231188(obj, s1, *(s32 *)((u8 *)obj + 0x8CC));
}
