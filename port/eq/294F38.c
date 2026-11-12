#include "common.h"

f32 sceVu0InnerProduct(s32 arg0, s32 arg1);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
void func_00312680(s32 arg0, s32 arg1, f32 farg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);

/* 0x00294F38 (BT3 ColSeg_NearestOnLine, fuzzy): nearest point of the line (or, unless infinite,
 * the segment) a + param * l to b. A line with squared length d below epsSq gives a (copied to
 * out, param untouched). Otherwise ab = b - a, param = dot(l, ab) / d, clamped to [0, 1] for a
 * segment, out = a + param * l. */
void ColSeg_NearestOnLine(f32 *arg0, f32 *arg1, f32 *arg2, s32 arg3, f32 farg0, f32 *arg4, f32 *arg5) {
    f32 ab[4];
    f32 d;
    f32 p;

    d = sceVu0InnerProduct((s32)arg1, (s32)arg1);
    if (d < farg0) {
        func_003126C8((s32)arg4, (s32)arg0);
        return;
    }

    func_00312650((s32)ab, (s32)arg2, (s32)arg0);
    p = sceVu0InnerProduct((s32)arg1, (s32)ab) / d;
    *arg5 = p;
    if (arg3 == 0) {
        if (p >= 1.0f) {
            p = 1.0f;
        } else if (p < 0.0f) {
            p = 0.0f;
        }
        *arg5 = p;
    }

    func_00312680((s32)arg4, (s32)arg1, *arg5);
    func_00312638((s32)arg4, (s32)arg4, (s32)arg0);
}
