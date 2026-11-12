#include "common.h"

void *BtlMember_GetActiveGauge(void *arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002668D0(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_00385948;

void func_00206450(u8 *arg0) {
    s32 s0;
    s32 i;
    s32 v0;
    s32 v1;
    f32 f;
    f32 frac;
    u8 *gauge;

    s0 = 0;
    if (*(s64 *)(arg0 + 0x338) & 0x40000) {
        f = *(f32 *)(arg0 + 0x9B0) * D_00385948;
        i = (s32)f;
        frac = f - (f32)i;
        if (frac > 0.5f || (frac == 0.5f && (i & 1))) {
            i += 1;
        } else if (frac < -0.5f || (frac == -0.5f && (i & 1))) {
            i -= 1;
        }
        v0 = (i < 0x7530) ? i : 0x752F;
        s0 = (v0 > 0) ? v0 : 0;
    }
    if (func_00211310((s32)arg0, 0, 0x800) == 0) {
        gauge = (u8 *)BtlMember_GetActiveGauge(arg0);
        v1 = *(s32 *)(gauge + 0x1C);
        if (s0 < v1) {
            s0 = v1;
        }
    }
    if (s0 <= 0) {
        return;
    }
    func_002668D0(*(s32 *)(arg0 + 0x1530), s0, 0x7530);
}
