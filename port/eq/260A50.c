#include "m2c_macros.h"

extern void EftShotFx_UpdateLines(void);
extern void Vu0Cur_StoreMtx(s32 arg0);
extern void func_0029D2D8(s32 arg0, s32 arg1);
extern void func_0029D5E0(f32 farg0, f32 farg1, f32 farg2);
extern s32 func_003126C8(s32 arg0, s32 arg1);
extern s32 memcmp(s32 arg0, s32 arg1, s32 arg2);
extern s32 sceVu0InversMatrix(s32 arg0, s32 arg1);
extern f32 D_00386E90;
extern f32 D_00386E94;

void func_00260A50(u8 *arg0) {
    u8 *s0;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    f32 f20;
    f32 f1;
    s32 s5;

    s0 = arg0 + 0x9B0;
    s2 = arg0 + 0x9A0;
    s3 = arg0 + 0x9E0;
    s4 = arg0 + 0x9D0;
    f20 = *(f32 *)(s2 + 0x54);
    s5 = memcmp((s32)s0, (s32)s3, 0x10) != 0;
    *(s32 *)(arg0 + 0x9BC) = 0;
    *(f32 *)(arg0 + 0x9AC) = 1.0f;
    func_003126C8((s32)s4, (s32)s2);
    func_003126C8((s32)s3, (s32)s0);
    s0 = arg0 + 0xA00;
    f1 = *(f32 *)(s2 + 0x44) + D_00386E90;
    *(f32 *)(s2 + 0x44) = f1;
    if (D_00386E90 < f1) {
        *(f32 *)(s2 + 0x44) = f1 - D_00386E94;
    }
    EftShotFx_UpdateLines();
    func_0029D2D8((s32)s4, (s32)s3);
    func_0029D5E0(f20, f20, f20);
    Vu0Cur_StoreMtx((s32)s0);
    sceVu0InversMatrix((s32)(arg0 + 0xA40), (s32)s0);
    *(s8 *)(arg0 + 0xAEC) = (s8)~s5;
}
