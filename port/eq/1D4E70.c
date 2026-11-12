#include "common.h"

extern u8 *D_00387E9C;

void *func_001D4E10(s32 arg0, void *arg1, void *arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                    f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7);
void func_00129C28(s32 arg0, s32 arg1);

/* 0x001D4E70: spawns a 0x80-byte record from the allocator func_001D4E10 and bumps the counter at D+0x142C. */
s32 func_001D4E70(s32 arg0, void *arg1, void *arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                  f32 sarg0, f32 sarg8, f32 sarg10, s32 sarg18, s32 sarg20, f32 sarg28) {
    u8 fr[0x50];
    u8 *rec;
    u8 *g;
    s32 t0;
    s32 k;
    f32 f0;

    t0 = arg4 & 0xFF;
    for (k = 0; k < 16; k++) {
        fr[k] = ((u8 *)arg1)[k];
        fr[0x10 + k] = ((u8 *)arg2)[k];
        fr[0x20 + k] = ((u8 *)arg3)[k];
    }
    *(s32 *)(fr + 0x30) = t0;

    rec = (u8 *)func_001D4E10(sarg18, arg1, arg2, arg3, t0, arg5, arg6, arg7,
                              farg0, farg1, farg2, farg3, farg4, farg5, farg6, farg7);
    if (rec == NULL) {
        return 0;
    }

    *(s32 *)rec = arg0;
    func_00129C28((s32)(rec + 0x10), (s32)fr);
    func_00129C28((s32)(rec + 0x20), (s32)(fr + 0x10));
    func_00129C28((s32)(rec + 0x30), (s32)(fr + 0x20));

    *(f32 *)(rec + 0x40) = farg0;
    f0 = 0.0f;
    if (farg1 != 0.0f) {
        f0 = 1.0f / farg1;
    }
    *(f32 *)(rec + 0x44) = f0;
    *(f32 *)(rec + 0x48) = farg2;
    *(f32 *)(rec + 0x4C) = farg3;
    *(f32 *)(rec + 0x50) = farg4;
    *(f32 *)(rec + 0x54) = farg5;
    *(f32 *)(rec + 0x58) = farg6;
    if (sarg0 == 0.0f) {
        *(f32 *)(rec + 0x5C) = farg6;
        f0 = (-farg6) / (sarg8 * 30.0f);
    } else {
        *(f32 *)(rec + 0x5C) = 0.0f;
        f0 = farg6 / (sarg0 * 30.0f);
    }
    *(f32 *)(rec + 0x60) = f0;
    *(f32 *)(rec + 0x64) = farg7;
    if (sarg0 == 0.0f) {
        f0 = sarg8 * 30.0f;
    } else {
        f0 = (sarg8 - sarg0) * 30.0f;
    }
    *(f32 *)(rec + 0x68) = f0;
    *(f32 *)(rec + 0x70) = sarg28;
    *(f32 *)(rec + 0x6C) = sarg10 * 30.0f;

    *(u8 *)(rec + 0x75) = (u8)arg5;
    *(u8 *)(rec + 0x74) = (u8)t0;
    *(u8 *)(rec + 0x76) = (u8)arg6;
    *(u8 *)(rec + 0x78) = (u8)arg7;
    *(u8 *)(rec + 0x79) = (u8)sarg18;
    *(u8 *)(rec + 0x7A) = (u8)sarg20;
    *(u8 *)(rec + 0x7B) = 1;
    *(u8 *)(rec + 0x77) = 0;
    *(u8 *)(rec + 0x7C) = 0;

    g = D_00387E9C;
    *(s32 *)(g + 0x142C) += 1;
    return *(s32 *)(g + 0x142C);
}
