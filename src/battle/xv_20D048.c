#include "common.h"

s32 func_001FBE80(s32 arg0, f32 farg0, f32 farg1);
s32 func_0020A658(s32 arg0);
s32 func_00211270(void);
s32 func_00211288(s32 arg0);
f32 func_0029DFD0(s32 arg0);
s32 func_00312650(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387930;

/* when D_00387930 is set: for every slot i (func_00211270() of them) without func_0020A658(i): obj = func_00211288(i);
 * t = func_0029DFD0 of the vector func_00312650(obj + 0x180, arg0); when t < farg1 the weight v = 1 - (t - farg0) /
 * (farg1 - farg0), clamped to [0, 1], calls func_001FBE80(obj, farg2 * v, farg3 * v) */
void func_0020D048(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    s32 sp[4];
    s32 i;
    if (D_00387930 != 0) {
        for (i = 0; i < func_00211270(); i++) {
            if (func_0020A658(i) == 0) {
                s32 obj = func_00211288(i);
                f32 t;
                func_00312650((s32)sp, obj + 0x180, arg0);
                t = func_0029DFD0((s32)sp);
                if (t < farg1) {
                    f32 v = 1.0f - ((t - farg0) / (farg1 - farg0));
                    if (v > 1.0f) {
                        v = 1.0f;
                    }
                    if (v < 0.0f) {
                        v = 0.0f;
                    }
                    func_001FBE80(obj, farg2 * v, farg3 * v);
                }
            }
        }
    }
}
