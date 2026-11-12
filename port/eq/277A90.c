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

void func_00276FD0(f32 arg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 rand(void);
extern f32 D_00387078;
extern f32 D_0038707C;
extern u8 D_00388D68[];

void func_00277A90(void) {
    f32 temp_f;
    s32 temp_r;
    s32 temp_a0;
    s32 temp_v0;
    s32 var_a0;
    s32 temp_b;
    s32 temp_c;

    var_a0 = *(s32 *)(D_00388D68 + 0xC);
    if (var_a0 == 0) {
        var_a0 = (rand() % 90) + 0x5A;
        *(s32 *)(D_00388D68 + 0xC) = var_a0;
    }
    temp_v0 = var_a0 - 1;
    *(s32 *)(D_00388D68 + 0xC) = temp_v0;
    if (temp_v0 <= 0) {
        temp_a0 = (rand() % 90) + 0x5A;
        *(s32 *)(D_00388D68 + 0xC) = temp_a0;
        temp_b = rand();
        temp_f = ((f32)temp_b / D_00387078) * 30.0f;
        BT2_CVT_NE(temp_f, temp_r);
        temp_c = rand();
        func_00297FE0(2, 0xA, temp_r + 0x5E, temp_c % 127, 0);
    }
    func_00276FD0(D_0038707C);
}
