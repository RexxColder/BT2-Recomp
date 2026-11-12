#include "common.h"

extern f32 D_00384AC8;
extern f32 D_00384ACC;
extern f32 D_00384AD0;
extern f32 D_00384AD4;
extern f32 D_00384AD8;
extern f32 D_00384ADC;
extern f32 D_00384AE0;
extern f32 D_00384AE4;
extern f32 D_00384AE8;

s32 rand(void);
void func_003126C8(u8 *arg0, u8 *arg1);

/* work: EftBoltWork; flash[20] at +0x5B0, 0x70 bytes each (BT3 EftBoltFlash layout). */
s32 EftBolt_AddFlash(u8 *work, s32 kind, s32 nodeA, s32 nodeB, u8 *vel, f32 size, f32 follow) {
    u8 *f = NULL;
    s32 i;
    f32 life;
    f32 rot;

    for (i = 0; i < 20; i++) {
        u8 *p = work + 0x5B0 + i * 0x70;
        if (*(s32 *)p == 0) {
            f = p;
            break;
        }
    }
    if (f == NULL) {
        return 0;
    }

    *(s32 *)f = *(s32 *)f | 1;
    *(s32 *)(f + 0x10) = kind;
    if (kind == 0) {
        *(f32 *)(f + 0x14) = 6.0f;
        *(f32 *)(f + 0x50) = D_00384ACC;
        *(f32 *)(f + 0x54) = D_00384AD0;
        *(f32 *)(f + 0x58) = D_00384AC8;
        *(f32 *)(f + 0x5C) = D_00384AC8;
    } else {
        *(f32 *)(f + 0x14) = 3.0f;
        *(f32 *)(f + 0x50) = D_00384AD4;
        *(f32 *)(f + 0x54) = D_00384AD4;
        *(f32 *)(f + 0x58) = D_00384AD4;
        *(f32 *)(f + 0x5C) = D_00384AD8;
    }
    *(s32 *)(f + 0x4) = nodeA;
    *(s32 *)(f + 0x8) = nodeB;
    func_003126C8(f + 0x40, vel);
    *(f32 *)(f + 0x24) = follow;
    *(f32 *)(f + 0x18) = size;

    life = *(f32 *)(f + 0x14);
    *(f32 *)(f + 0x1C) = -(size * D_00384ADC) / life;
    *(f32 *)(f + 0x20) = -(*(f32 *)(f + 0x5C) / (life + 1.0f));

    *(s32 *)(f + 0xC) = rand() % 4;

    rot = (f32)rand() / D_00384AE0 * D_00384AE4;
    *(f32 *)(f + 0x28) = rot;
    if (D_00384AE8 <= rot) {
        *(f32 *)(f + 0x28) = rot - D_00384AE4;
    }
    return 1;
}
