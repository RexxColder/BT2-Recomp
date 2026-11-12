#include "m2c_macros.h"

void func_00312650(void *a0, void *a1, void *a2);
void func_003125D0(void *a0, void *a1, f32 f12);
void func_00312680(void *a0, void *a1, f32 f12);

/* Object O (arg0; skipped when flag 0x2 at +0x164 is set). The two range values at +0x60 and +0x64 are
 * clamped to at least 1.0, four vectors at +0x90..+0x13F are rebuilt with them, and the two ratios at
 * +0x74 and +0x78 are derived from +0x80..+0x88. */
void Obj_UpdateScaleVecs(u8 *arg0) {
    u8 *o;
    f32 k;
    f32 r1;
    f32 r2;

    o = arg0;
    if ((*(u32 *)(o + 0x164) & 2) != 0) {
        return;
    }
    k = 1.0f;
    r1 = *(f32 *)(o + 0x6C) - *(f32 *)(o + 0x68);
    r2 = *(f32 *)(o + 0x70) - *(f32 *)(o + 0x6C);
    if (r1 < k) {
        r1 = 1.0f;
    }
    *(f32 *)(o + 0x60) = r1;
    *(f32 *)(o + 0x64) = r2;
    if (r2 < k) {
        *(f32 *)(o + 0x64) = 1.0f;
    }

    func_00312650(o + 0x90, o + 0xD0, o + 0xC0);
    func_00312650(o + 0xA0, o + 0xE0, o + 0xD0);
    func_003125D0(o + 0x90, o + 0x90, *(f32 *)(o + 0x60));
    func_003125D0(o + 0xA0, o + 0xA0, *(f32 *)(o + 0x64));
    func_00312680(o + 0x90, o + 0x90, k);
    func_00312680(o + 0xA0, o + 0xA0, k);

    func_00312650(o + 0xF0, o + 0x130, o + 0x120);
    func_00312650(o + 0x100, o + 0x140, o + 0x130);
    func_003125D0(o + 0xF0, o + 0xF0, *(f32 *)(o + 0x60));
    func_003125D0(o + 0x100, o + 0x100, *(f32 *)(o + 0x64));
    func_00312680(o + 0xF0, o + 0xF0, k);
    func_00312680(o + 0x100, o + 0x100, k);

    *(f32 *)(o + 0x74) = (*(f32 *)(o + 0x84) - *(f32 *)(o + 0x80)) / *(f32 *)(o + 0x60);
    *(f32 *)(o + 0x78) = (*(f32 *)(o + 0x88) - *(f32 *)(o + 0x84)) / *(f32 *)(o + 0x64);
}
