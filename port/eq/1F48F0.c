#include "common.h"

#define BT2_CVT_NE(x, dst)                                                              \
    do {                                                                                \
        f32 cx_ = (x);                                                                  \
        s32 ct_ = (s32)cx_;                                                             \
        f32 cr_ = cx_ - (f32)ct_;                                                       \
        if (cr_ > 0.5f || (cr_ == 0.5f && (ct_ & 1))) {                                 \
            ct_++;                                                                      \
        } else if (cr_ < -0.5f || (cr_ == -0.5f && (ct_ & 1))) {                        \
            ct_--;                                                                      \
        }                                                                               \
        (dst) = ct_;                                                                    \
    } while (0)

s32 func_001F4588(s32 arg0);
void func_002837C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283800(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283770(s32 arg0, void *arg1, s32 arg2);
extern u8 *D_00387920;

void func_001F48F0(s32 arg0) {
    f32 f1;
    f32 f2;
    f32 f3;
    s32 t0v;
    s32 s0v;
    s32 s1v;

    if (D_00387920 != NULL) {
        if (func_001F4588(arg0) == 1) {
            f2 = *(f32 *)(D_00387920 + 0x48);
            f3 = f2 * 8.0f;
            f1 = f2 * 32.0f;
            f2 = f2 * 128.0f;
            BT2_CVT_NE(f3, t0v);
            BT2_CVT_NE(f1, s0v);
            BT2_CVT_NE(f2, s1v);
            func_002837C0(0, 0x80, 0x80, 0x80, t0v & 0xFF);
            func_00283800(0, 0x80, 0x80, 0x80, s0v & 0xFF);
            func_00283840(0, 0x80, 0x80, 0x80, s1v & 0xFF);
            func_00283770(0, D_00387920 + 0x50, 0);
        }
    }
}
