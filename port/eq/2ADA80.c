#include "common.h"

void *func_002B1DD0(s32 arg0);
void memset(void *arg0, s32 arg1, s32 arg2);
extern f32 D_0038731C;
extern u8 *D_00387A40;
extern u8 *D_00387E18;
extern s32 D_003B2654 __attribute__((section(".data")));

void func_002ADA80(void) {
    u8 *q;
    u8 *a;
    u8 *base;
    s32 v;
    s32 s0;
    s32 s1;
    s32 n;
    f32 f21;

    if (D_00387E18 == NULL) {
        return;
    }
    v = *(s32 *)(D_00387E18 + 4);
    if (v <= 0) {
        return;
    }
    base = *(u8 **)D_00387E18;
    if (base == NULL) {
        return;
    }
    memset(base, 0, v * 0x1A0);
    if (*(s32 *)(D_00387E18 + 4) > 0) {
        f21 = D_0038731C;
        s1 = 0;
        s0 = 0;
        do {
            q = func_002B1DD0(s0);
            *(s32 *)(q + 4) = s0;
            *(s32 *)(q + 0x10) = s0;
            s0 += 1;
            *(s32 *)(q + 0xC) = -1;
            a = *(u8 **)(D_00387A40 + 8) + s1;
            *(u8 **)(q + 0) = a;
            *(s32 *)(q + 8) = *(s32 *)(a + 0x10);
            *(f32 *)(q + 0x74) = f21;
            *(s32 *)(q + 0x1C) = -1;
            *(u8 *)(q + 0x20) = (u8)(*(s32 *)(a + 0xC) != 0);
            *(f32 *)(q + 0x150) = 1.0f;
            *(f32 *)(q + 0x16C) = 1.0f;
            *(u8 *)(q + 0x7C) = 1;
            s1 += 0x1520;
        } while (s0 < *(s32 *)(D_00387E18 + 4));
    }
    q = func_002B1DD0(0);
    *(s32 *)(q + 0xC) = 0;
    if (D_003B2654 < 0) {
        n = *(s32 *)(D_00387E18 + 4);
        if (n >= 2) {
            q = func_002B1DD0(n - 2);
            *(s32 *)(q + 0x10) = 3;
        }
    }
}
