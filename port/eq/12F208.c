#include "common.h"

f32 func_0029DFD0(void *arg0);
void func_00208AA0(s32 arg0, void *arg1);
extern u8 *gEftBubble;

void func_0012F208(s32 arg0) {
    s32 sp[4];
    f32 temp_f0;
    u8 *temp_s0;

    if (gEftBubble != NULL) {
        temp_s0 = *(u8 **)gEftBubble + arg0 * 16;
        if (!(temp_s0[0xC] & 2)) {
            func_00208AA0(arg0, sp);
            temp_f0 = func_0029DFD0(sp) * 5.0f;
            *(s32 *)(temp_s0 + 0) = arg0;
            if (temp_f0 < 40.0f) {
                *(f32 *)(temp_s0 + 8) = 40.0f;
            } else if (!(temp_f0 > 60.0f)) {
                *(f32 *)(temp_s0 + 8) = temp_f0;
            } else {
                *(f32 *)(temp_s0 + 8) = 60.0f;
            }
            *(s32 *)(temp_s0 + 4) = 0;
            temp_s0[0xC] = temp_s0[0xC] | 2;
        }
    }
}
