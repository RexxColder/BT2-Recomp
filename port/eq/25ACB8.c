#include "common.h"

void CamShake_Add(s32 arg0, f32 farg0, f32 farg1);
extern u8 *D_00387A30;

void func_0025ACB8(f32 arg0) {
    if (*(s32 *)(D_00387A30 + 0x2B0) != 0) {
        CamShake_Add((s32)(D_00387A30 + 0x2FC), 1.0f, arg0);
    }
}
