#include "common.h"

extern f32 D_00383E44;

s32 func_0010B080(void);
s32 func_0010B0A0(s32 arg0);
void func_0010EBF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_0010ED48(s32 arg0, f32 farg0);
void BtlRec_CallFlagged(s32 arg0, s32 arg1, s32 arg2);
s32 func_00113B00(s32 arg0, s32 arg1, s32 arg2);
void func_00113CB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001140A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00114508(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00203CC0(s32 arg0);
f32 Ramp_Start(s32 arg0, f32 farg0, f32 farg1, f32 farg2);
s32 Ramp_Step(s32 arg0);

void func_0010EEA0(s32 arg0, s32 arg1, s32 arg2) {
    u8 *ret0;
    u8 *s2;
    u8 *s4;
    u8 *s5;
    u8 *base1;
    u8 *rec;
    u8 *src;
    u8 *dst;
    u8 *ptr;
    s32 temp_lo;
    s32 s3;
    s32 idx;
    s32 v;
    s32 t;
    f32 x;
    s64 q0;
    s64 q1;
    s64 q2;
    s64 q3;

    ret0 = (u8 *)func_0010B080();
    s2 = (u8 *)func_00203CC0(arg2);
    base1 = (u8 *)arg0 + arg1 * 0x750;
    s4 = (u8 *)(func_0010B0A0(arg1) + 0x1500);
    func_00114508((s32)s4, 2, 0, 0xF);
    s5 = base1 + 0xD0;

    temp_lo = *(s32 *)(s2 + 0x14) / 100000;
    s3 = *(s32 *)(s2 + 0x14) % 100000;
    func_0010EBF0((s32)s4, temp_lo, 7, 0x10, 0x22);
    if (*(s32 *)(s5 + 0x704) < temp_lo) {
        *(s32 *)(s5 + 0x700) = 0x80;
    }
    *(s32 *)(s5 + 0x704) = temp_lo;
    t = *(s32 *)(s5 + 0x700) - 0x10;
    *(s32 *)(s5 + 0x700) = (t < 0) ? 0 : t;

    if (*(s32 *)(s2 + 0x14) == *(s32 *)(s2 + 0x18)) {
        base1 = base1 + 0x114;
        if (Ramp_Step((s32)base1) != 0) {
            if (*(f32 *)(s5 + 0x54) == 1.0f) {
                Ramp_Start((s32)base1, 1.5f, 1.0f, 0.0f);
            } else {
                /* asm 0x0010EFBC: el delay slot del bc1f carga a0 = s1 (base1) tambien en esta rama */
                Ramp_Start((s32)base1, 1.5f, 0.0f, 1.0f);
            }
        }
        src = s4;
        dst = s4 + 0x240;
        do {
            q0 = *(s64 *)(src + 0x00);
            q1 = *(s64 *)(src + 0x08);
            q2 = *(s64 *)(src + 0x10);
            q3 = *(s64 *)(src + 0x18);
            *(s64 *)(dst + 0x00) = q0;
            *(s64 *)(dst + 0x08) = q1;
            *(s64 *)(dst + 0x10) = q2;
            *(s64 *)(dst + 0x18) = q3;
            src += 0x20;
            dst += 0x20;
        } while (src != s4 + 0x60);
        *(s16 *)(s4 + 0x254) = 0x13;
        x = *(f32 *)(s5 + 0x54) * 127.0f;
        t = (s32)x;
        {
            f32 frac = x - (f32)t;
            if (frac > 0.5f || (frac == 0.5f && (t & 1))) {
                t += 1;
            } else if (frac < -0.5f || (frac == -0.5f && (t & 1))) {
                t -= 1;
            }
        }
        *(u8 *)(s4 + 0x259) = (u8)t;
    } else {
        Ramp_Start((s32)(base1 + 0x114), 1.5f, 0.0f, 1.0f);
    }

    if (*(s32 *)(s5 + 0x700) > 0) {
        src = s4;
        dst = s4 + 0x300;
        do {
            q0 = *(s64 *)(src + 0x00);
            q1 = *(s64 *)(src + 0x08);
            q2 = *(s64 *)(src + 0x10);
            q3 = *(s64 *)(src + 0x18);
            *(s64 *)(dst + 0x00) = q0;
            *(s64 *)(dst + 0x08) = q1;
            *(s64 *)(dst + 0x10) = q2;
            *(s64 *)(dst + 0x18) = q3;
            src += 0x20;
            dst += 0x20;
        } while (src != s4 + 0x60);
        *(s16 *)(s4 + 0x314) = 0x13;
        *(u8 *)(s4 + 0x319) = (u8)*(u8 *)(s5 + 0x700);
    }

    idx = 0;
    if (*(s32 *)(s5 + 0x694) & 1) {
        func_0010ED48((s32)(s4 + 0x3C0), (f32)s3 / D_00383E44);
        idx = 0;
    }

    s3 = idx * 8;
    do {
        ptr = s5 + 8 + s3 + 0x700;
        v = *(s32 *)ptr;
        if (v > 0) {
            rec = s4 + idx * 0x60 + 0x60;
            func_00113CB8((s32)rec, 0, *(s32 *)(ret0 + 8), (s16)(idx + 0xE));
            func_00113B00((s32)rec, *(s32 *)ptr + 7, *(s32 *)(s5 + 8 + s3 + 0x704) - 3);
            idx = idx + 1;
            if (((*(s32 *)(s5 + 0x698)) >> idx) & 1) {
                *(u8 *)(rec + 0x18) = 0x16;
                *(u8 *)(rec + 0x16) = 0x16;
                *(u8 *)(rec + 0x17) = 0x16;
            }
        } else {
            *(s32 *)(s4 + idx * 0x60 + 0x60) = 0;
            idx = idx + 1;
        }
        s3 = idx * 8;
    } while (idx < 4);

    if (arg1 == 1) {
        func_001140A8((s32)s4, 0, 1, 0, 0xF);
    }
    BtlRec_CallFlagged((s32)s4, 1, 0xF);
}
