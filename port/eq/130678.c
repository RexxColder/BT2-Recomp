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

void Vu0Screen_StoreMtx(void *arg0);
s32 func_00126588(void);
void func_001308C8(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg8, f32 farg9);
void func_003126C8(void *arg0, void *arg1);
extern u8 *gEftBubble;

void func_00130678(void *arg0) {
    s32 sp[20];
    void *sp40;
    u8 *var_s1;
    s32 temp_v1;
    s32 t1v;
    f32 f0v;
    f32 f12v;
    f32 f13v;

    sp40 = &sp[16];
    var_s1 = (u8 *)arg0;
    Vu0Screen_StoreMtx(sp);
    if (var_s1 != NULL) {
        do {
            if (*(u8 *)(var_s1 + 0x55) != 0) {
                func_003126C8(sp40, var_s1);
                temp_v1 = *(s32 *)(var_s1 + 0x4C);
                if ((temp_v1 == func_00126588()) || (temp_v1 == -1)) {
                    f0v = *(f32 *)(var_s1 + 0x2C);
                    f12v = *(f32 *)(var_s1 + 0x24);
                    f13v = *(f32 *)(var_s1 + 0x28);
                    BT2_CVT_NE(f0v, t1v);
                    if (f0v >= 2147483648.0f) {
                        f0v = f0v - 2147483648.0f;
                        BT2_CVT_NE(f0v, t1v);
                    }
                    t1v = t1v & 0xFF;
                    func_001308C8(sp40, sp, *(u8 *)(var_s1 + 0x50), *(u8 *)(var_s1 + 0x51),
                                  *(u8 *)(var_s1 + 0x52), t1v,
                                  (s32)(gEftBubble + (*(u8 *)(var_s1 + 0x53) << 4) + 0x68),
                                  *(u8 *)(var_s1 + 0x54), f12v, f13v);
                }
            }
            var_s1 = *(u8 **)(var_s1 + 0x5C);
        } while (var_s1 != NULL);
    }
}
