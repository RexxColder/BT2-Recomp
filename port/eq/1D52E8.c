#include "common.h"

#define RNE_S32(x, out) do { \
    f32 t_ = (x); \
    s32 i_ = (s32)t_; \
    f32 d_ = t_ - (f32)i_; \
    if (d_ > 0.5f || (d_ == 0.5f && (i_ & 1))) { i_++; } \
    else if (d_ < -0.5f || (d_ == -0.5f && (i_ & 1))) { i_--; } \
    (out) = i_; \
} while (0)

extern u8 *D_00387E9C;
extern f32 D_003854D8;

void Mtx_StoreIdentity(s32 arg0);
void Vu0Screen_StoreMtx(s32 arg0);
void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);
void func_001DA8B8(s32 arg0, s32 arg1);
void func_00208798(s32 arg0, s32 arg1);
void func_001DAF18(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7);

void func_001D52E8(void) {
    u8 fr[0xb0];   /* tamano de locales del original (antes 0xa0) */
    u8 *s0;
    s32 s3;
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    f32 x;

    if (*(s32 *)(D_00387E9C + 0x142C) != 0) {
        Vu0Screen_StoreMtx((s32)(fr + 0x10));
        s3 = 0x18;
        s0 = *(u8 **)(D_00387E9C + 0x1408);
        do {
            if (s0[0x7B] != 0 && s0[0x7C] != 0) {
                switch (s0[0x78]) {
                case 0:
                    func_00129C28((s32)(fr + 0x50), (s32)(s0 + 0x10));
                    break;
                case 1:
                    func_00208798(*(s32 *)s0, (s32)(fr + 0x50));
                    func_00129B28((s32)(fr + 0x50), (s32)(fr + 0x50), (s32)(s0 + 0x10));
                    break;
                }
                Mtx_StoreIdentity((s32)(fr + 0x60));
                func_001DA8B8((s32)(fr + 0x60), (s32)(s0 + 0x30));

                x = *(f32 *)(D_00387E9C + 0x14A0) * *(f32 *)(s0 + 0x70);
                RNE_S32(x, w0);
                x = *(f32 *)(D_00387E9C + 0x14A4) * *(f32 *)(s0 + 0x70);
                RNE_S32(x, w1);
                x = *(f32 *)(D_00387E9C + 0x14A8) * *(f32 *)(s0 + 0x70);
                RNE_S32(x, w2);
                x = *(f32 *)(D_00387E9C + 0x14AC) * 0.0078125f;
                x = *(f32 *)(s0 + 0x5C) * x;
                RNE_S32(x, w3);
                if (w3 < 0) {
                    w3 = 0;
                }
                if (255.0f < (f32)w3) {
                    w3 = 255;
                }

                func_001DAF18((s32)(fr + 0x50), (s32)(fr + 0x60), (s32)(fr + 0x10),
                              (u8)w0, (u8)w1, (u8)w2, (u8)w3,
                              (s32)(D_00387E9C + 0x14B0 + (s0[0x79] << 4)), s0[0x7A],
                              *(f32 *)(s0 + 0x48), 1.0f, 0.0f, D_003854D8, 0.0f, 0.0f, 1.0f, 1.0f);
            }
            s3 -= 1;
            s0 += 0x80;
        } while (s3 >= 0);
    }
}
