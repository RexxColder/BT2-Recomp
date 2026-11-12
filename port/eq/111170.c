#include "common.h"

#define RND_NEAREST(x, out)                                              \
    do {                                                                 \
        f32 rx_ = (x);                                                   \
        s32 ri_ = (s32)rx_;                                              \
        f32 rd_ = rx_ - (f32)ri_;                                        \
        if (rd_ > 0.5f || (rd_ == 0.5f && (ri_ & 1))) {                  \
            ri_ += 1;                                                    \
        } else if (rd_ < -0.5f || (rd_ == -0.5f && (ri_ & 1))) {         \
            ri_ -= 1;                                                    \
        }                                                                \
        (out) = ri_;                                                     \
    } while (0)

u8 *func_0010B078(void);
u8 *func_0010B080(void);
void Ramp_Start(void *arg0, f32 farg0, f32 farg1, f32 farg2);
s32 Ramp_Step(void *arg0, f32 farg0, f32 farg1, f32 farg2);
void func_00112B28(s32 arg0);
void func_00113CB8(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00113B00(void *arg0, s32 arg1, s32 arg2);
void func_001138D0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0);
void func_00113430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, s32 t1, s32 t2);
void *memset(void *, s32, u32);
extern f32 D_00383E9C;
extern f32 D_00383EA0;
extern f32 D_00383EA4;
extern f32 D_00383EA8;
extern f32 D_00383EAC;
extern f32 D_00383EB0;

s32 func_00111170(void) {
    u8 frame[0x140];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *temp_a0;
    s32 t0;
    f32 f0;

    s0 = func_0010B078();
    s1 = s0 + 0xB4;
    s2 = func_0010B080();
    temp_a0 = s0 + 0xB8;
    if (*(s32 *)s1 == 0) {
        Ramp_Start(temp_a0, D_00383E9C, 1.0f, D_00383EA0);
        *(s32 *)s1 = *(s32 *)s1 + 1;
    } else if (Ramp_Step(temp_a0, D_00383E9C, 1.0f, D_00383EA0) != 0) {
        if (*(f32 *)(s1 + 0x14) == 1.0f) {
            Ramp_Start(temp_a0, D_00383EA4, 1.0f, D_00383EA8);
        } else {
            Ramp_Start(temp_a0, D_00383EAC, D_00383EB0, 1.0f);
        }
    }
    memset(frame, 0, 0x120);
    func_00112B28(*(s32 *)(s2 + 0x14));
    func_00113CB8(frame, 0, *(s32 *)(s2 + 0x14), 0);
    s0 = frame + 0x60;
    func_00113CB8(s0, 0, *(s32 *)(s2 + 0x14), 1);
    func_00113B00(frame, 0x100, 8);
    func_00113B00(s0, 0x80, 0x140);

    f0 = *(f32 *)(s1 + 0x14) * 128.0f;
    if (2147483648.0f <= f0) {
        RND_NEAREST(f0 - 2147483648.0f, t0);
        t0 = t0 | (s32)0x80000000;
    } else {
        RND_NEAREST(f0, t0);
    }
    t0 = t0 & 0xFF;
    func_001138D0(frame + 0x76, 0x80, 0x80, 0x80, t0);
    *(s32 *)(frame + 0xC0) = 2;
    func_00113430(*(s32 *)(s2 + 0x14), (s32)frame, 1, 0x2A00, 0x2C80, 0, 0);
    return 0;
}
