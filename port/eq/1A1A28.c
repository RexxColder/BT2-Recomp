#include "common.h"

#define AT(T, p, off) (*(T *)((u8 *)(p) + (off)))

void func_003126C8(u8 *arg0, s32 arg1);
s32 rand(void);
void sceVu0Normalize(f32 *arg0, f32 *arg1);

extern f32 D_00384E20;
extern f32 D_00384E24;
extern f32 D_00384E28;
extern f32 D_00384E2C;
extern f32 D_00384E30;
extern f32 D_00384E34;
extern f32 D_00384E38;
extern f32 D_00384E3C;

void func_001A1A28(u8 *arg0, s32 arg1, f32 *arg2) {
    u8 *s0;
    s32 s2;
    s32 x;

    s0 = arg0 + 0x30;
    s2 = 0;
    do {
        if (!(AT(s32, s0, 0x48) & 1)) {
            func_003126C8(s0, arg1);
            AT(f32, s0, 0x10) = arg2[0] + ((((f32)rand() / D_00384E20) * 0.5f) - 0.25f);
            AT(f32, s0, 0x14) = arg2[1] + ((((f32)rand() / D_00384E20) * D_00384E28) - D_00384E2C);
            AT(f32, s0, 0x18) = arg2[2] + ((((f32)rand() / D_00384E20) * 0.5f) - 0.25f);
            sceVu0Normalize((f32 *)(s0 + 0x10), (f32 *)(s0 + 0x10));
            AT(f32, s0, 0x20) = 1.0f;
            AT(f32, s0, 0x28) = D_00384E30;
            AT(f32, s0, 0x24) = D_00384E34;
            AT(s32, s0, 0x48) = 1;
            AT(s32, s0, 0x44) = rand() % 3;
            AT(f32, s0, 0x2C) = (2.0f * (((f32)rand() / D_00384E20) * D_00384E24)) - D_00384E24;
            AT(f32, s0, 0x30) = (((f32)rand() / D_00384E20) * D_00384E38) - D_00384E3C;
            x = rand();
            AT(s32, s0, 0x38) = 0;
            AT(f32, s0, 0x34) = ((f32)x / D_00384E20) + 1.0f;
            x = rand();
            AT(s32, s0, 0x40) = 0;
            AT(s32, s0, 0x50) = 1;
            AT(s32, s0, 0x54) = 1;
            AT(s32, s0, 0x4C) = (s2 < 5) ? 0 : 7;
            AT(f32, s0, 0x3C) = ((f32)x / D_00384E20) + 0.5f;
        }
        s2 += 1;
        s0 += 0x60;
    } while (s2 < 5);
}
