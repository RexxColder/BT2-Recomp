#include "common.h"

extern u8 *D_0038777C;
extern f32 D_003849C4;

s32 func_00129C28(void *a0, void *a1);
void Vec4_Set(f32 *a0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
s32 func_00208DE8(u8 *a0, f32 *a1, s32 a2);
void func_00129B58(f32 *a0, f32 *a1, f32 *a2);
f32 func_00129CD8(f32 *a0, f32 *a1);
void EftAura_SpawnSpark(u8 *a0, u8 *a1, s32 a2, s32 a3, f32 *a4, f32 farg0);
s32 rand(void);
void *memset(void *arg0, s32 arg1, u32 arg2);
f32 sqrtf(f32 farg0);
f32 fabsf(f32 farg0);

/* 0x00179548 (EftAura_SpawnSparks): spawns arg3-controlled sparks around the object arg0.
 * sqrt.s (EE) takes |x|; the sqrtf fallback of the original is only reached on NaN. */
void EftAura_SpawnSparks(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    f32 v00[4];
    f32 v10[4];
    f32 v20[4];
    f32 v30[4];
    f32 v40[4];
    u8 *entry;
    s32 s1;
    s32 s5;
    s32 s6;
    s32 flag;
    s32 i;
    f32 f20;
    f32 f21;
    f32 d;

    memset(v40, 0, 16);
    flag = arg3 & 0xFF;
    entry = D_0038777C + arg2 * 8 + 0x4A0;
    s6 = *(s32 *)(entry + 4);
    s1 = *(s32 *)(entry + 8);
    f21 = *(f32 *)(D_0038777C + 0x1D0) * *(f32 *)(arg0 + 0x64);
    func_00129C28(v00, arg0 + arg2 * 16 + 0x330);

    Vec4_Set(v20, 0.0f, 0.0f, 0.0f, 1.0f);
    s5 = 1;
    if (s1 >= 0) {
        func_00208DE8(arg1, v10, s1);
        func_00129B58(v30, v10, v00);
        d = func_00129CD8(v30, v30);
        f20 = sqrtf(fabsf(d));
        func_00129C28(v20, v30);
        if (f21 < f20) {
            s5 = (s32)(f20 / f21 + 1.0f);
        }
    }

    f20 = D_003849C4;
    for (i = 0; i < s5; i++) {
        EftAura_SpawnSpark(arg0, arg1, arg2, s6, v40, (f32)rand() / f20);
        if (flag != 0) {
            break;
        }
    }
}
