#include "common.h"

void Vu0Screen_StoreMtx(void *arg0, s64 arg1);
void sceVu0InterVectorXYZ(f32 farg0, void *arg0, s64 *arg1, void *arg2);
void func_00141DD0(void *arg0, void *arg1, void *arg2);
void func_00140FA0(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
extern u8 D_0036DD30[] __attribute__((section(".data")));
extern u8 D_002C3630[] __attribute__((section(".data")));
extern u8 *gEftDust;

void func_001404A0(u8 *arg0) {
    s32 sp10[16] __attribute__((aligned(16)));
    s32 sp50[16] __attribute__((aligned(16)));
    s32 spA0[4] __attribute__((aligned(16)));
    s64 sp90;
    u8 *s0;

    sp90 = *(s64 *)(D_0036DD30 + 0x0);
    Vu0Screen_StoreMtx(sp50, *(s64 *)(D_0036DD30 + 0x8));

    s0 = arg0;
    while (s0 != NULL) {
        if (*(u8 *)(s0 + 0x94) != 0) {
            sceVu0InterVectorXYZ(*(f32 *)(s0 + 0x44), spA0, &sp90, s0 + 0x20);
            func_00141DD0(sp10, spA0, D_002C3630);

            {
                /* cvt.w.s (truncates toward zero) of the 0x58 float, high bit when >= 2^31 */
                f32 f0 = *(f32 *)(s0 + 0x58);
                f32 xv = f0;
                s32 hi = 0;
                f32 tt;
                s32 rr;
                s32 t3v;

                if (f0 >= 2147483648.0f) {
                    xv = f0 - 2147483648.0f;
                    hi = (s32)0x80000000;
                }
                tt = xv;
                rr = (s32)tt;
                t3v = (s32)((u32)rr | (u32)hi);
                t3v = t3v & 0xFF;

                func_00140FA0(*(f32 *)(s0 + 0x70), *(f32 *)(s0 + 0x4C), *(f32 *)(s0 + 0x78), 0.0f, *(f32 *)(s0 + 0x7C),
                              (s32)s0, (s32)sp10, (s32)sp50, *(u8 *)(s0 + 0x8C), *(u8 *)(s0 + 0x8D), *(u8 *)(s0 + 0x8E), 0x40, t3v,
                              (s32)(gEftDust + ((*(u8 *)(s0 + 0x91)) << 4) + 0xB0), *(u8 *)(s0 + 0x92));
            }
        }
        s0 = *(u8 **)(s0 + 0x9C);
    }
}
