#include "common.h"

void Rigid_AddForceAt(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_003871B8;

void Rigid_AddGravity(u8 *arg0) {
    s32 sp[4];
    f32 v = *(f32 *)(arg0 + 0x8) * D_003871B8;

    sp[0] = 0;
    *(f32 *)&sp[1] = v;
    sp[2] = 0;
    Rigid_AddForceAt((s32)arg0, (s32)(arg0 + 0x30), (s32)sp);
}
