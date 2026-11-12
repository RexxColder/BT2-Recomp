#include "common.h"

extern f32 D_003874DC;
extern f32 D_003874E0;

void EftRay_CreateByValue(void *a0, s64 a1, s64 a2, s32 a3);
void EftGlow_Request(s32 a0, s32 a1);
void EftAura_Command(s32 a0, s32 a1);
void func_001A1748(s32 a0);
void func_001C9448(s32 a0);
void func_001C9510(s32 a0);
s32 func_0025FBE8(void *a0, s64 a1);
void func_002837C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_00283800(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_00283840(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_00283770(s32 a0, void *a1, s32 a2);
void sceVu0Normalize(void *a0, void *a1);
void func_002B1CA8(void *a0, s32 a1);

void func_002AFC28(void *arg0) {
    u8 fr[0x100] = {0};
    u8 *a = (u8 *)arg0;
    s32 s1;
    s32 s3;
    s32 s4;
    s32 s5;
    s32 t;
    s32 i;
    f32 f0;
    f32 f1;
    f32 x;
    s32 r8;
    s32 r32;
    s32 r128;

    s1 = *(s32 *)(a + 0x24);
    s5 = *(s32 *)(a + 0x28) & ~s1;
    s4 = s1 & ~*(s32 *)(a + 0x28);

    if (s1 & 2) {
        memset(fr + 0x60, 0, 0x10);
        *(f32 *)(fr + 0x6C) = 1.0f;
        *(s32 *)(fr + 0x78) = 0x80;
        *(f32 *)(fr + 0x80) = 1.0f;
        *(f32 *)(fr + 0x84) = 800.0f;
        *(f32 *)(fr + 0x88) = 1.5f;
        *(f32 *)(fr + 0x90) = 50.0f;
        *(s32 *)(fr + 0x94) = 2;
        *(s32 *)(fr + 0x98) = 0x30;
        *(s32 *)(fr + 0x9C) = *(s32 *)(a + 4);
        fr[0xB0] = 1;
        *(s32 *)(fr + 0x70) = 0x80;
        *(s32 *)(fr + 0x74) = 0x80;
        *(s32 *)(fr + 0x8C) = 0;
        *(s32 *)(fr + 0xA0) = 1;
        *(s32 *)(fr + 0xA4) = 1;
        *(s32 *)(fr + 0xA8) = 0;
        *(s32 *)(fr + 0xAC) = 0;
        *(s32 *)(fr + 0x7C) = 0x40;
        for (i = 0; i < 0x60; i += 8) {
            *(s64 *)(fr + i) = *(s64 *)(fr + 0x60 + i);
        }
        EftRay_CreateByValue(fr, *(s64 *)(fr + 0xB0), *(s64 *)(fr + 0xB8), *(s32 *)(a + 4));
    }

    t = *(s32 *)((u8 *)*(s32 *)a + 0x958);
    s3 = s1 & 1;
    if ((t != 0) && !(*(s32 *)((u8 *)t + 0x30) & 0x10)) {
        if (s4 & 1) {
            EftGlow_Request(*(s32 *)(a + 4), 0);
        }
        if (s5 & 1) {
            EftGlow_Request(*(s32 *)(a + 4), 1);
            EftAura_Command(*(s32 *)(a + 4), 1);
        }
        s3 = s1 & 1;
    }

    f0 = *(f32 *)(a + 0x34);
    if (s3 != 0) {
        f0 = f0 + D_003874DC;
        if (1.0f < f0) {
            f0 = 1.0f;
        }
    } else {
        f0 = f0 - D_003874E0;
        if (f0 < 0.0f) {
            f0 = 0.0f;
        }
    }
    *(f32 *)(a + 0x34) = f0;

    if (*(s32 *)(a + 4) == 0) {
        f1 = *(f32 *)(a + 0x34);

        /* cvt.w.s = truncates toward zero; the value is in [0, 1] here */
        x = f1 * 8.0f;
        r8 = (s32)x;
        x = f1 * 32.0f;
        r32 = (s32)x;
        x = f1 * 128.0f;
        r128 = (s32)x;

        func_002837C0(0, 0x80, 0x80, 0x80, r8 & 0xFF);
        func_00283800(*(s32 *)(a + 4), 0x80, 0x80, 0x80, r32 & 0xFF);
        func_00283840(*(s32 *)(a + 4), 0x80, 0x80, 0x80, r128 & 0xFF);
        if (s3 != 0) {
            sceVu0Normalize(fr + 0x60, a + 0x130);
            func_00283770(*(s32 *)(a + 4), fr + 0x60, 0);
        }
    }

    if (*(s32 *)((u8 *)*(s32 *)a + 4) == 0x2E) {
        if (s4 & 4) {
            func_001C9448(*(s32 *)(a + 4));
        }
        if (s5 & 4) {
            func_001C9510(*(s32 *)(a + 4));
        }
    }

    if (func_0025FBE8((void *)*(s32 *)a, (s64)0x20) != 0) {
        *(s32 *)((u8 *)*(s32 *)a + 0xAF0) |= 0x20;
    }
    if (func_0025FBE8((void *)*(s32 *)a, (s64)0x40) != 0) {
        *(s32 *)((u8 *)*(s32 *)a + 0xAF0) &= -0x21;
    }
    if (func_0025FBE8((void *)*(s32 *)a, (s64)0x8000 << 28) != 0) {
        *(s32 *)((u8 *)*(s32 *)a + 0xAF0) |= 0x40;
    }
    if (func_0025FBE8((void *)*(s32 *)a, (s64)0x8000 << 29) != 0) {
        *(s32 *)((u8 *)*(s32 *)a + 0xAF0) &= -0x41;
    }
    if (*(s32 *)((u8 *)*(s32 *)a + 0xAF0) & 0x200) {
        *(s32 *)((u8 *)*(s32 *)a + 0xAF0) &= -0x3E01;
        func_001A1748(*(s32 *)(a + 4));
        func_002B1CA8(arg0, 0x20);
    }
}
