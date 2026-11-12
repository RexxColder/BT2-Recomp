#include "common.h"

void func_001EC370(s32 arg0, s32 arg1);
s32 func_003126C8(s32 arg0, s32 arg1);
s32 sceVu0UnitMatrix(s32 arg0);
s32 rand(s32 arg0);
extern f32 D_00384F40;
extern f32 D_00384F44;
extern f32 D_00384F48;

void func_001AF898(u8 *a0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    u8 *s0;
    u8 *s2;
    f32 tmp;

    s2 = a0 + 0xC0;
    s0 = a0 + 0x80;
    *(f32 *)(s0 + 0xC0) = ((f32)rand((s32)a0) / D_00384F40) * D_00384F44 - D_00384F48;
    if (*(u8 *)(a0 + 0x5A) == 0) {
        farg0 = -farg0;
    }
    *(f32 *)(s0 + 0xC4) = farg0;
    *(s32 *)(s0 + 0xC8) = 0;
    *(s32 *)(s0 + 0xCC) = 0;
    *(u8 *)(s0 + 0xE0) = 0;
    *(u8 *)(s0 + 0xE1) = 0;
    *(f32 *)(s0 + 0xDC) = farg3 * 30.0f;
    *(u8 *)(s0 + 0xE2) = 0;
    func_001EC370((s32)s2, *(s32 *)(a0 + 0x40));
    sceVu0UnitMatrix((s32)s2);
    sceVu0UnitMatrix((s32)s0);
    func_003126C8((s32)(a0 + 0xF0), (s32)a0);
    func_003126C8((s32)(a0 + 0xB0), (s32)a0);
    if (farg2 == 0.0f) {
        *(f32 *)(s0 + 0xD0) = farg1;
        return;
    }
    *(f32 *)(s0 + 0xD0) = 0.5f;
    tmp = farg1 - 0.5f;
    *(f32 *)(s0 + 0xD4) = tmp;
    *(f32 *)(s0 + 0xD4) = tmp / (farg2 * 30.0f);
    *(f32 *)(s0 + 0xD8) = farg1;
    *(u8 *)(s0 + 0xE1) = (u8)(*(u8 *)(s0 + 0xE1) | 2);
}
