#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 func_00312650(s32 arg0, s32 arg1, s32 arg2);
f32 func_0029DFD0(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* when func_00211310(arg0, 3, 0x10000) is set: the 3-entry tables of both objects (+0x1534) are filled, the
 * height of arg0 * 5.0f clamped to [20, 150] is compared with func_0029DFD0 of the combined table and func_002113C0
 * (arg0, 4, 0x40, 1) is called when it is below; always returns 0 */
s32 func_001FD460(s32 arg0, s32 arg1) {
    s32 sp[4];
    s32 sp10[4];
    s32 sp20[4];
    f32 f20;
    s32 r = func_00211310(arg0, 3, 0x10000);
    if (r != 0) {
        func_00208DE8(*(s32 *)((u8 *)arg0 + 0x1534), (s32)sp, 3);
        func_00208DE8(*(s32 *)((u8 *)arg1 + 0x1534), (s32)sp10, 3);
        f20 = BtlCharApi_GetHeight(*(s32 *)((u8 *)arg0 + 0x1534)) * 5.0f;
        if (f20 < 20.0f) {
            f20 = 20.0f;
        }
        if (f20 > 150.0f) {
            f20 = 150.0f;
        }
        func_00312650((s32)sp20, (s32)sp, (s32)sp10);
        if (func_0029DFD0((s32)sp20) < f20) {
            func_002113C0(arg0, 4, 0x40, 1);
        }
        r = 0;
    }
    return r;
}
