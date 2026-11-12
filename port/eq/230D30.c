#include "common.h"

extern s32 func_002411E0(s32 obj, s32 a1);
extern s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_001FA230(s32 obj, f32 frame);
extern s32 func_0025FBE8(s32 arg0, s64 arg1);
extern void *BtlChar_GetPos(s32 obj);
extern void func_0020D048(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
extern void func_0020D240(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
extern void func_001FBE80(s32 arg0, f32 farg0, f32 farg1);
extern void BtlChar_Vibrate(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_00386854;
extern f32 D_00386858;
extern f32 D_0038685C;
extern f32 D_00386860;
extern f32 D_00386864;
extern f32 D_00386868;
extern f32 D_0038686C;
extern f32 D_00386870;
extern f32 D_00386874;
extern f32 D_00386878;

/* Hit feedback: sparks when flag 0x4000000 is set, else shake + vibrate. The tail calls return void
   functions (their stale v0 is not modelled: 0 returned). */
s32 func_00230D30(s32 obj, s32 a1, s32 mode) {
    s32 ev;
    s32 frame;

    if (mode == 0) {
        if ((func_002411E0(obj, a1) & 0x800000) == 0) {
            return 0;
        }
        ev = BtlObjAnim_QueryEvent(*(s32 *)(obj + 0x1530), 0x400, 0, 2);
        if (ev == 1) {
            frame = BtlObjAnim_QueryEvent(*(s32 *)(obj + 0x1530), 0x400, 0, 0) - 4;
            if (frame < 0) {
                frame = 0;
            }
            if (func_001FA230(obj, (f32)frame) == 0) {
                return 0;
            }
            if ((func_002411E0(obj, a1) & 0x4000000) != 0) {
                func_0020D048(BtlChar_GetPos(obj), 100.0f, 1000.0f, 10.0f, D_00386854);
                func_0020D240(BtlChar_GetPos(obj), 100.0f, 1000.0f, 1.0f, D_00386858);
            } else {
                func_001FBE80(obj, 10.0f, D_0038685C);
                BtlChar_Vibrate(obj, 1.0f, D_00386860);
            }
            return 0;
        }
        if (ev < 2) {
            return 1;
        }
        if (func_0025FBE8(*(s32 *)(obj + 0x1530), 0x400) == 0) {
            return 0;
        }
        if ((func_002411E0(obj, a1) & 0x4000000) != 0) {
            func_0020D048(BtlChar_GetPos(obj), 100.0f, 1000.0f, 10.0f, D_00386864);
            func_0020D240(BtlChar_GetPos(obj), 100.0f, 1000.0f, 1.0f, D_00386868);
        } else {
            func_001FBE80(obj, 10.0f, D_0038686C);
            BtlChar_Vibrate(obj, 1.0f, D_00386870);
        }
        return 0;
    }
    if (mode == 1) {
        if ((func_002411E0(obj, a1) & 0x1000000) == 0) {
            return 0;
        }
        if ((func_002411E0(obj, a1) & 0x4000000) != 0) {
            func_0020D048(BtlChar_GetPos(obj), 100.0f, 1000.0f, 3.0f, D_00386874);
            func_0020D240(BtlChar_GetPos(obj), 100.0f, 1000.0f, 1.0f, D_00386874);
        } else {
            func_001FBE80(obj, 3.0f, D_00386878);
            BtlChar_Vibrate(obj, 1.0f, D_00386878);
        }
        return 0;
    }
    return 1;
}
