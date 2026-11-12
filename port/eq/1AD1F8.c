#include "common.h"

void Vec3_Add(void *arg0, void *arg1, void *arg2);
void func_00129C28(void *arg0, void *arg1);
f32 EftMath_WrapAngle(f32 farg0);
void func_001AD690(s32 arg0);
extern f32 D_00384F14;

/* 0x001AD1F8 (BT3 EftKiObj_Step, fuzzy): one frame of a prop ki blast. Frame counter at +0xE4
 * (u16), flags at +0xC0 (0x2 moved, 0x8 dead, 0x10 broken), model at +0x11C (-1 = gone),
 * pos +0x50, prev +0x60, vel +0x70, gravity +0xE0 (added to vel.y), spin angle at +0xD8 from
 * (frame * spinRate) % 360 scaled by pi/180, fragment timer at +0x1C4. */
s32 EftKiObj_Step(u8 *arg0) {
    u8 *w = *(u8 **)(arg0 + 0x38);
    s32 sr;
    s32 rem;

    *(u16 *)(w + 0xE4) = (u16)(*(u16 *)(w + 0xE4) + 1);
    if (*(s32 *)(w + 0x11C) == -1) {
        *(u32 *)(w + 0xC0) |= 0x8;
    }
    if ((*(u32 *)(w + 0xC0) & 0x10) == 0) {
        if ((*(u32 *)(w + 0xC0) & 0x2) != 0) {
            func_00129C28(w + 0x60, w + 0x50);
        }
        *(u32 *)(w + 0xC0) |= 0x2;
        Vec3_Add(w + 0x50, w + 0x50, w + 0x70);
        *(f32 *)(w + 0x74) = *(f32 *)(w + 0x74) + *(f32 *)(w + 0xE0);
    }

    /* spinRate (float) truncated by cvt.w.s, then (frame * rate) % 360 */
    sr = (s32)*(f32 *)(w + 0xDC);
    rem = (s32)*(s16 *)(w + 0xE4) * sr % 360;
    *(f32 *)(w + 0xD8) = EftMath_WrapAngle(((f32)rem / 180.0f) * D_00384F14);
    if (*(s16 *)(w + 0x1C4) <= 0) {
        *(u32 *)(w + 0xC0) |= 0x8;
    }
    func_001AD690((s32)arg0);
    return 0;
}
