#include "common.h"

s64 __divdi3(s64 a, s64 b);
s32 func_002E0A98(s32 a0, s32 a1, s32 a2);
s32 func_00325830(u8 *a0, u8 *a1, void *a2, s64 a3, s64 t0, s64 t1, s64 t2, s64 t3,
                  s64 st0, s64 st1, s64 st2, s64 st3, s64 st4, s64 st5, s64 st6, s64 st7,
                  s64 st8, s64 st9, s64 st10, s64 st11, s64 st12, s64 st13, s64 st14,
                  s64 st15, s64 st16, s64 st17, s64 st18);
void strcpy(u32 dst, u8 *src);

extern s32 D_00346C0C __attribute__((section(".data")));
extern s32 D_00346E84 __attribute__((section(".data")));
extern s32 D_00346E88 __attribute__((section(".data")));
extern u32 D_00346E90 __attribute__((section(".data")));
extern u32 D_00346E94 __attribute__((section(".data")));
extern u8 D_0037A6B8[] __attribute__((section(".data")));

void func_002D3988(u8 *arg0) {
    u8 spA0[0x100];
    s64 temp_v0;
    s64 temp_s1;
    s64 temp_v1;
    s64 ld188;
    s64 ld108;
    s32 temp_s6;
    s32 temp_s0;

    if (D_00346E88 == 0) {
        return;
    }
    temp_s6 = func_002E0A98(0x3E8, *(s32 *)(arg0 + 0x118), *(s32 *)(arg0 + 0x120));
    temp_s1 = *(s64 *)(arg0 + 0x118);
    temp_v0 = __divdi3(temp_s1, *(s64 *)(arg0 + 0x120));
    temp_v1 = *(s64 *)(arg0 + 0x128);
    ld188 = *(s64 *)(arg0 + 0x188);
    ld108 = *(s64 *)(arg0 + 0x108);
    temp_s0 = func_00325830(spA0, D_0037A6B8, arg0, temp_v0, (s64)temp_s6, temp_s1 >> 32,
                            temp_s1, temp_s1 & 0x7FFFFFFF,
                            ld188, ld108, temp_v1, ld108 - temp_v1, ld188 - temp_v1,
                            (s64)*(s32 *)(arg0 + 0x1AC), (s64)*(s32 *)(arg0 + 0x1B0),
                            (s64)*(s32 *)(arg0 + 0x1B4), (s64)*(s32 *)(arg0 + 0x1B8),
                            (s64)*(u32 *)(arg0 + 0x4), (s64)*(u32 *)(arg0 + 0x8),
                            (s64)*(s32 *)(arg0 + 0x19C), (s64)*(s32 *)(arg0 + 0x1A0),
                            (s64)*(s32 *)(arg0 + 0x190), (s64)*(s32 *)(arg0 + 0x194),
                            (s64)*(s32 *)(arg0 + 0x198), (s64)*(s32 *)(arg0 + 0x1A4),
                            (s64)*(s32 *)(arg0 + 0x1A8), (s64)D_00346C0C);
    strcpy(D_00346E90, spA0);
    D_00346E90 = D_00346E90 + temp_s0;
    if (D_00346E90 >= (u32)((D_00346E88 + D_00346E84) - 0x400)) {
        D_00346E90 = D_00346E94;
    }
}
