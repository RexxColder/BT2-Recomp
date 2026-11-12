#include "common.h"

extern s64 D_0036DD20[] __attribute__((section(".data")));
extern u8 D_002C3630[] __attribute__((section(".data")));
extern s32 gEftDust;

void Vu0Screen_StoreMtx(void *arg0, s32 arg1, s64 arg2);
void func_00141DD0(void *arg0, void *arg1, void *arg2);
void func_00312638(void *arg0, void *arg1, s32 arg2);
void sceVu0InterVectorXYZ(f32 farg0, void *arg0, void *arg1, void *arg2);
void func_00140FA0(f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void *a0, void *a1, void *a2,
                   s32 a3, s32 t0, s32 t1, s32 t2, s32 t3, s32 st0, s32 st1);

void EftWaterSpray_DrawList(u8 *arg0, s32 arg1) {
    s64 sp90[2];
    f32 sp10[16];
    f32 spA0[4];
    f32 sp50[16];
    f32 spB0[4];
    u8 *s1;
    f32 f0, x;
    s32 t3v, k;

    sp90[1] = D_0036DD20[1];
    sp90[0] = D_0036DD20[0];
    Vu0Screen_StoreMtx(sp50, arg1, D_0036DD20[0]);
    if (arg0 != NULL) {
        for (s1 = arg0; s1 != NULL; s1 = *(u8 **)(s1 + 0x8C)) {
            if (*(s32 *)(s1 + 0x84) & 2) {
                sceVu0InterVectorXYZ(*(f32 *)(s1 + 0x40), spB0, sp90, s1 + 0x30);
                func_00141DD0(sp10, spB0, D_002C3630);
                func_00312638(spA0, s1, arg1);
                spA0[3] = 1.0f;
                f0 = *(f32 *)(s1 + 0x54);
                if (f0 >= 2147483648.0f) {
                    x = f0 - 2147483648.0f;
                    k = (s32)x;
                    if (x - (f32)k > 0.5f || (x - (f32)k == 0.5f && (k & 1))) {
                        k++;
                    } else if (x - (f32)k < -0.5f || (x - (f32)k == -0.5f && (k & 1))) {
                        k--;
                    }
                    t3v = (s32)((u32)k | 0x80000000u);
                } else {
                    k = (s32)f0;
                    if (f0 - (f32)k > 0.5f || (f0 - (f32)k == 0.5f && (k & 1))) {
                        k++;
                    } else if (f0 - (f32)k < -0.5f || (f0 - (f32)k == -0.5f && (k & 1))) {
                        k--;
                    }
                    t3v = k;
                }
                t3v &= 0xFF;
                func_00140FA0(*(f32 *)(s1 + 0x60), *(f32 *)(s1 + 0x48), *(f32 *)(s1 + 0x68), 0.0f,
                              *(f32 *)(s1 + 0x6C), spA0, sp10, sp50,
                              s1[0x7C], s1[0x7D], s1[0x7E], 0x40, t3v,
                              gEftDust + ((s32)s1[0x7F] << 4) + 0xB0, s1[0x80]);
            }
        }
    }
}
