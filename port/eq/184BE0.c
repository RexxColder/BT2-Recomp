#include "common.h"

f32 Rand_FloatRange(f32 arg0, f32 arg1);
void func_00129BD0(u8 *arg0, u8 *arg1, f32 farg0);
f32 Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00184F48(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4);
f32 func_00184DD0(f32 farg0, f32 farg1, u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, s32 arg4);
u8 *func_00185CD0(void);
void func_00185C38(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00185C68(u8 *arg0, u8 *arg1, u8 *arg2);

s32 func_00184BE0(u8 *arg0) {
    f32 fr[12];
    u8 *sp;
    u8 *sp10;
    u8 *sp20;
    u8 *s0;
    u8 *s2;
    u8 *s4;
    u8 *s5;
    s32 s6;
    s32 s7;
    s32 bound;
    s32 do9;
    s32 v0;
    f32 f21;
    f32 f20;
    f32 t;
    s32 i;
    f32 r;

    s6 = 0;
    s4 = *(u8 **)(arg0 + 0x30);
    s7 = *(s32 *)(arg0 + 0x34);
    s2 = *(u8 **)(arg0 + 0x1A4);
    f21 = *(f32 *)(arg0 + 0x88) / *(f32 *)(s4 + 0x94);
    if (f21 < 1.0f) {
        return 0;
    }

    /* cvt.w.s of f21 (truncates toward zero) */
    t = f21;
    i = (s32)t;
    bound = i;

    sp = (u8 *)fr;
    sp10 = sp + 0x10;
    sp20 = sp + 0x20;
    while (s6 < bound) {
        s5 = arg0 + 0x70;
        f20 = (f32)s6;
        func_00129BD0(sp20, s5, *(f32 *)(s4 + 0x94) * f20);
        r = Rand_FloatRange(*(f32 *)(s4 + 0x98), *(f32 *)(s4 + 0x9C));
        func_00129BD0(sp10, s5, r);
        Vec3_Add(sp20, sp20, sp10);
        Vec3_Add(sp, arg0 + 0x50, sp20);

        do9 = 0;
        if (s2 != 0) {
            s0 = s2;
            if ((*(u16 *)(s2 + 0xBE) & 2) == 0) {
                do9 = 1;
            }
        } else {
            s0 = func_00185CD0();
            if (s0 == 0) {
                break;
            }
            s2 = s0;
            func_00185C38(arg0 + 0x1A4, arg0 + 0x1A8, s0);
            do9 = 1;
        }
        if (do9 != 0) {
            func_00184F48(s0, s4, s7, *(u8 *)(arg0 + 0x199), *(u8 *)(arg0 + 0x198));
            func_00184DD0(*(f32 *)(arg0 + 0x80), *(f32 *)(s4 + 0x20) * f20, s0, s4, sp, s5, s6);
            *(u16 *)(s0 + 0xBE) = (u16)(*(u16 *)(s0 + 0xBE) | 3);
        }
        s2 = *(u8 **)(s2 + 0xC0);
        s6 += 1;
    }

    if (s2 != 0) {
        v0 = *(u16 *)(s2 + 0xBE);
        do {
            if ((v0 & 2) == 0) {
                *(u16 *)(s2 + 0xBE) = 0;
                func_00185C68(arg0 + 0x1A4, arg0 + 0x1A8, s2);
            }
            s2 = *(u8 **)(s2 + 0xC0);
            if (s2 == 0) {
                break;
            }
            v0 = *(u16 *)(s2 + 0xBE);
        } while (1);
    }
    return 1;
}
