#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FL(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define B8(p, o) (*(u8 *)((u8 *)(p) + (o)))

extern f32 D_00384BCC;

void memset(void *arg0, s32 arg1, s32 arg2);
f32 Rand_FloatRange(f32 farg0, f32 farg1);
void Vec3_Sub(void *arg0, void *arg1, void *arg2);
void func_0018B788(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0018A8D0(void *arg0, s32 arg1, s32 arg2);

void func_00187EC0(u8 *arg0, u8 *arg1) {
    u8 *o;
    u8 *p;
    f32 f20;
    f32 f2;
    f32 sp0;
    f32 sp4;
    f32 sp10;
    f32 sp14;

    o = *(u8 **)(arg0 + 0x38);
    memset(o, 0, 0x1F0);
    if (FL(arg1, 0x1C) != 1.0f) {
        FL(arg1, 0x1C) = 1.0f;
    }
    f20 = D_00384BCC;
    W(o, 0x30) = W(arg1, 0);
    W(o, 0x34) = W(arg1, 4);
    func_0018B788(o, W(arg1, 8), W(arg1, 0x58), W(arg1, 0x58));
    W(o, 0xD0) = W(arg1, 0x5C);
    *(s64 *)(o + 0x40) = *(s64 *)(arg1 + 0x10);
    *(s64 *)(o + 0x48) = *(s64 *)(arg1 + 0x18);
    *(s64 *)(o + 0x50) = *(s64 *)(arg1 + 0x20);
    *(s64 *)(o + 0x58) = *(s64 *)(arg1 + 0x28);
    *(s64 *)(o + 0x60) = *(s64 *)(arg1 + 0x20);
    *(s64 *)(o + 0x68) = *(s64 *)(arg1 + 0x28);
    Vec3_Sub(o + 0x70, arg1 + 0x30, arg1 + 0x20);
    { void bt2_fightlog_note(const char *fmt, ...); f32 *a_ = (f32 *)(o + 0x50), *d_ = (f32 *)(o + 0x70);
      bt2_fightlog_note("BEAMPOS init obj %p id %X inicio %.1f %.1f %.1f dir %.1f %.1f %.1f largo %.1f", o, *(u32 *)(arg1 + 8),
                        a_[0], a_[1], a_[2], d_[0], d_[1], d_[2], __builtin_sqrtf(d_[0] * d_[0] + d_[1] * d_[1] + d_[2] * d_[2])); }
    FL(o, 0xC0) = FL(arg1, 0x54) * 30.0f;

    p = *(u8 **)arg1;
    sp0 = FL(p, 0xA8) * 30.0f;
    sp4 = (FL(p, 0xAC) - FL(p, 0xA8)) * 30.0f;
    FL(o, 0x88) = Rand_FloatRange(FL(p, 0xB8), FL(p, 0xB8) + FL(p, 0xC4));
    sp10 = Rand_FloatRange(FL(p, 0xBC), FL(p, 0xBC) + FL(p, 0xC8));
    sp14 = Rand_FloatRange(FL(p, 0xC0), FL(p, 0xC0) + FL(p, 0xCC));
    FL(o, 0x8C) = (sp10 - FL(o, 0x88)) / sp0;
    FL(o, 0x90) = (sp14 - sp10) / sp4;
    FL(o, 0x80) = FL(arg1, 0x50);

    FL(o, 0xAC) = Rand_FloatRange(FL(p, 0xD0), FL(p, 0xD0) + FL(p, 0xDC)) * f20;
    sp10 = Rand_FloatRange(FL(p, 0xD4), FL(p, 0xD4) + FL(p, 0xE0)) * f20;
    sp14 = Rand_FloatRange(FL(p, 0xD8), FL(p, 0xD8) + FL(p, 0xE4)) * f20;
    FL(o, 0x98) = (sp10 - FL(o, 0xAC)) / sp0;
    FL(o, 0x9C) = (sp14 - sp10) / sp4;

    FL(o, 0xB0) = Rand_FloatRange(FL(p, 0xE8), FL(p, 0xE8) + FL(p, 0xF4)) * f20;
    sp10 = Rand_FloatRange(FL(p, 0xEC), FL(p, 0xEC) + FL(p, 0xF8)) * f20;
    sp14 = Rand_FloatRange(FL(p, 0xF0), FL(p, 0xF0) + FL(p, 0xFC)) * f20;
    FL(o, 0xA4) = (sp10 - FL(o, 0xB0)) / sp0;
    FL(o, 0xA8) = (sp14 - sp10) / sp4;

    f2 = FL(p, 0x94);
    FL(o, 0xB4) = f2;
    FL(o, 0xB8) = (FL(p, 0xB0) - f2) / sp0;
    FL(o, 0xBC) = (FL(p, 0xB4) - FL(p, 0xB0)) / sp4;
    W(o, 0xC8) = 0;
    W(o, 0xCC) = 0;

    W(o, 0x1D8) = W(o, 0x1D8) | 2;
    B8(o, 0x1D4) = (u8)W(arg1, 0x58);
    W(o, 0x1E0) = 0;
    W(o, 0x1E4) = 0;

    func_0018A8D0(o, B8(p, 0xA0), B8(p, 0xA1));
    B8(o, 0x1D5) = (u8)(B8(p, 0xA0) * B8(p, 0xA1));
}
