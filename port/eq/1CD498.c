#include "common.h"

void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void sceVu0DivVectorXYZ(s32 arg0, s32 arg1, f32 farg0);
f32 Rand_FloatRange(s32 arg0, s32 arg1, f32 farg0, f32 farg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);

void func_001CD498(s32 arg0, s32 arg1, s32 arg2) {
    s32 b[16];
    s32 *sp0;
    s32 *sp10;
    s32 *sp20;
    s32 *sp30;
    f32 r;

    sp0 = &b[0];
    sp10 = &b[4];
    sp20 = &b[8];
    sp30 = &b[12];
    func_00208DE8(arg2, (s32)sp0, *(s32 *)((u8 *)arg0 + 0));
    func_00208DE8(arg2, (s32)sp10, *(s32 *)((u8 *)arg0 + 4));
    Vec3_Sub((s32)sp20, (s32)sp10, (s32)sp0);
    sceVu0DivVectorXYZ((s32)sp20, (s32)sp20, (f32)*(s32 *)((u8 *)arg0 + 8));
    r = Rand_FloatRange(0, (s32)sp20, 0.0f, (f32)*(s32 *)((u8 *)arg0 + 8));
    func_00129BD0((s32)sp30, (s32)sp20, r);
    Vec3_Add(arg1, (s32)sp0, (s32)sp30);
}
