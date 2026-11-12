#include "common.h"

void func_00312650(void *arg0, void *arg1, void *arg2);
void func_00312680(void *arg0, void *arg1, f32 farg0);
void func_00312638(void *arg0, void *arg1, void *arg2);
void func_003125D0(void *arg0, void *arg1, f32 farg0);

/* 0x001E1BC8: per-frame update of the unit block st. Block at st + 0x60 keeps a time value (+0xC, floored from
   n * 0.5 + 0.5), the input n (+0x10), copies of the 4-word vector at st + 0x40 (+0x50, +0x60) and of src
   (+0x80), and three 16-byte frame vectors built from func_00312650/func_00312680/func_00312638 and
   func_003125D0. The 0x90 / 0xA0 pair and the +0x14 / +0x18 pair swap roles on the parity flag (t >= +0xC).
   The asm returns the last callee's v0 (void callee), so this is void. */
void func_001E1BC8(u8 *st, s32 t, s32 n, u8 *src) {
    u8 *s2 = st + 0x60;
    u8 *s3 = st + 0xC0;
    u8 *s4 = st + 0xD0;
    u8 *s5 = st + 0xE0;
    u8 v26[16];
    s32 s6;
    f32 fl;
    f32 fa;
    f32 fb;
    f32 fv;
    f32 fn;
    f32 ft;

    ft = (f32)t;
    fn = (f32)n;

    s6 = (ft < *(f32 *)(s2 + 0xC)) ? 0 : 1;

    *(s32 *)(s2 + 0x8) = 0;
    fl = __builtin_floorf(fn * 0.5f + 0.5f);
    *(f32 *)(s2 + 0x10) = fn;
    *(f32 *)(s2 + 0xC) = fl;

    *(s32 *)(s2 + 0x50) = *(s32 *)(st + 0x40);
    *(s32 *)(s2 + 0x54) = *(s32 *)(st + 0x44);
    *(s32 *)(s2 + 0x58) = *(s32 *)(st + 0x48);
    *(s32 *)(s2 + 0x5C) = *(s32 *)(st + 0x4C);
    *(s32 *)(s2 + 0x60) = *(s32 *)(st + 0x40);
    *(s32 *)(s2 + 0x64) = *(s32 *)(st + 0x44);
    *(s32 *)(s2 + 0x68) = *(s32 *)(st + 0x48);
    *(s32 *)(s2 + 0x6C) = *(s32 *)(st + 0x4C);
    *(s32 *)(s2 + 0x80) = *(s32 *)(src + 0x0);
    *(s32 *)(s2 + 0x84) = *(s32 *)(src + 0x4);
    *(s32 *)(s2 + 0x88) = *(s32 *)(src + 0x8);
    *(s32 *)(s2 + 0x8C) = *(s32 *)(src + 0xC);

    func_00312650((void *)v26, (void *)s5, (void *)s3);
    func_00312680((void *)v26, (void *)v26, 0.5f);
    func_00312638((void *)s4, (void *)s3, (void *)v26);

    fa = *(f32 *)(s2 + 0xC);
    fb = *(f32 *)(s2 + 0x10);
    *(f32 *)(s2 + 0x0) = fa - *(f32 *)(s2 + 0x8);
    if (((s32)fb & 1) != 0) {
        fv = fb - fa;
    } else {
        fv = (fb - 1.0f) - fa;
    }
    *(f32 *)(s2 + 0x4) = fv;

    func_00312650((void *)(s2 + 0x30), (void *)s4, (void *)s3);
    func_00312650((void *)(s2 + 0x40), (void *)s5, (void *)s4);
    func_003125D0((void *)(s2 + 0x30), (void *)(s2 + 0x30), *(f32 *)(s2 + 0x0));
    func_003125D0((void *)(s2 + 0x40), (void *)(s2 + 0x40), *(f32 *)(s2 + 0x4));
    func_00312680((void *)(s2 + 0x30), (void *)(s2 + 0x30), 1.0f);
    func_00312680((void *)(s2 + 0x40), (void *)(s2 + 0x40), 1.0f);

    if (s6 != 0) {
        __builtin_memcpy(s2 + 0x90, s2 + 0xA0, 16);
    } else {
        __builtin_memcpy(s2 + 0xA0, s2 + 0x90, 16);
    }

    if (s6 != 0) {
        *(s32 *)(s2 + 0x14) = *(s32 *)(s2 + 0x18);
    } else {
        *(s32 *)(s2 + 0x18) = *(s32 *)(s2 + 0x14);
    }
}
