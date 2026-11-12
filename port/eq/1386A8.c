#include "common.h"

void func_0012AAC0(s32 a0, void *a1, void *a2, s64 a3, s64 t0, s64 t1, s64 t2, s64 t3);
f32 sceVu0InnerProduct(void *a0, void *a1);
extern s64 D_0036DCB0[] __attribute__((section(".data")));
extern s64 D_0036DCE0[] __attribute__((section(".data")));
extern s32 gEftSurf;

void EftSurf_StepAnim(void) {
    s64 tbl[12];
    f32 vec[4];
    s32 s1;
    s32 s2;
    u8 *a;
    f32 f21;
    f32 ip;
    f32 f1;

    s1 = gEftSurf;
    a = (u8 *)(s1 + 0x240);
    s2 = s1 + 0x1300;
    f21 = (f32)*(s32 *)(a + 0x10B4) / (f32)*(s32 *)(a + 0x1104);

    tbl[0] = D_0036DCB0[0];
    tbl[1] = D_0036DCB0[1];
    tbl[2] = D_0036DCB0[2];
    tbl[3] = D_0036DCB0[3];
    tbl[4] = D_0036DCB0[4];
    tbl[5] = D_0036DCB0[5];
    tbl[6] = D_0036DCE0[0];
    tbl[7] = D_0036DCE0[1];
    tbl[8] = D_0036DCE0[2];
    tbl[9] = D_0036DCE0[3];
    tbl[10] = D_0036DCE0[4];
    tbl[11] = D_0036DCE0[5];

    vec[0] = -*(f32 *)(a + 0x10A0);
    vec[1] = -*(f32 *)(a + 0x10A4);
    vec[2] = -*(f32 *)(a + 0x10A8);
    vec[3] = 1.0f;

    func_0012AAC0(s2, tbl, &tbl[6], D_0036DCB0[4], D_0036DCE0[2], D_0036DCE0[3], D_0036DCE0[4], D_0036DCB0[3]);
    *(f32 *)(a + 0xE40) = sceVu0InnerProduct(vec, (void *)s2);
    *(f32 *)(a + 0xE44) = sceVu0InnerProduct(vec, (void *)(s1 + 0x1310));
    ip = sceVu0InnerProduct(vec, (void *)(s1 + 0x1320));
    *(f32 *)(a + 0xE4C) = 1.0f;
    *(f32 *)(a + 0xE48) = ip;

    f1 = *(f32 *)(a + 0x1118) + f21;
    *(f32 *)(a + 0x1118) = f1;
    if (f1 >= 1.0f) {
        *(f32 *)(a + 0x1118) = 0.0f;
        *(s32 *)(a + 0x1100) = *(s32 *)(a + 0x1100) + 1;
    }
    if (*(s32 *)(a + 0x1104) - 1 < *(s32 *)(a + 0x1100)) {
        *(s32 *)(a + 0x1100) = 0;
    }
}
