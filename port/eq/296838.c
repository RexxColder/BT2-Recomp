#include "common.h"

void Rigid_Damp(u8 *arg0, f32 farg0) {
    f32 v90;
    f32 v94;
    f32 v98;
    f32 vD0;
    f32 vD4;
    f32 vD8;

    v90 = *(f32 *)(arg0 + 0x90);
    v94 = *(f32 *)(arg0 + 0x94);
    v98 = *(f32 *)(arg0 + 0x98);
    vD0 = *(f32 *)(arg0 + 0xD0);
    vD4 = *(f32 *)(arg0 + 0xD4);
    vD8 = *(f32 *)(arg0 + 0xD8);
    *(f32 *)(arg0 + 0x90) = v90 - v90 * farg0;
    *(f32 *)(arg0 + 0x94) = v94 - v94 * farg0;
    *(f32 *)(arg0 + 0x98) = v98 - v98 * farg0;
    *(f32 *)(arg0 + 0xD0) = vD0 - vD0 * farg0;
    *(f32 *)(arg0 + 0xD4) = vD4 - vD4 * farg0;
    *(f32 *)(arg0 + 0xD8) = vD8 - vD8 * farg0;
}
