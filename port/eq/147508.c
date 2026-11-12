#include "common.h"

void func_00145A30(s32 arg0, s32 arg1, s32 arg2);
void func_00145A58(s32 arg0, s32 arg1, s32 arg2);
s32 func_00145A80(s32 arg0);

void func_00147508(s32 arg0, s32 arg1) {
    f32 sp[4];
    s32 v1;

    func_00145A30((s32)sp, arg0, arg1);
    sp[3] = 250.0f;
    v1 = func_00145A80((s32)sp);
    if (v1 != 0) {
        do {
            *(s32 *)(arg0 + 0x28) = 8;
            if (v1 & 1) {
                sp[0] = sp[0] + (-500.0f);
            }
            if (v1 & 2) {
                sp[0] = sp[0] - (-500.0f);
            }
            if (v1 & 4) {
                sp[1] = sp[1] + (-500.0f);
            }
            if (v1 & 8) {
                sp[1] = sp[1] - (-500.0f);
            }
            if (v1 & 0x10) {
                sp[2] = sp[2] + (-500.0f);
            }
            if (v1 & 0x20) {
                sp[2] = sp[2] - (-500.0f);
            }
            v1 = func_00145A80((s32)sp);
        } while (v1 != 0);
    }
    func_00145A58(arg0, arg1, (s32)sp);
}
