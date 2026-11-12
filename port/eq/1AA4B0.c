#include "common.h"

/* called twice: first with the eight argument registers set, then with a0/a1 only (unprototyped) */
void func_00129C28();
s32 EftRibbon_Create(s32 arg0);
void EftRibbon_SetTexFrame(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 EftRibbon_SetUnk5C(s32 arg0, s32 arg1);
s32 memset(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_00384EDC;
extern u8 *D_003876A0;
extern u8 *D_00387848;

/* cvt.w.s truncates toward zero (saturating): plain cast, dst = (s32)x */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(dst, x) do { \
    (dst) = (s32)(x); \
} while (0)

f32 func_001AA4B0(s32 arg0) {
    s64 fr[16];             /* the 0x80-byte stack frame, addressed by byte offset as in the asm */
    u8 *S = (u8 *)fr;
    u8 *s0;
    u8 *s1;
    u8 *s2;
    f32 f0;
    f32 t;
    s64 t0v;
    s64 t1v;
    s64 t2v;
    s64 t3v;
    s64 a2v;
    s64 a3v;
    s64 v0v;
    s64 v1v;
    s32 x;
    s32 c;
    s32 temp_v0;

    s0 = *(u8 **)(arg0 + 0x38);
    s2 = D_00387848 + 0x258;
    f0 = *(f32 *)(s0 + 0x6C);
    s1 = D_00387848 + 8;
    if (!(f0 <= 0.0f)) {
        *(u8 *)(S + 0x40) = 0;
        *(s32 *)(S + 0x44) = (s32)*(s16 *)(s0 + 0x52);
        *(f32 *)(S + 0x48) = 0.0f;
        t = *(f32 *)(*(u8 **)s1 + 0xA8) * *(f32 *)(s0 + 0x2C);
        *(f32 *)(S + 0x4C) = t;
        memset((s32)(S + 0x50), 0, 0x10);
        memset((s32)(S + 0x60), 0, 0x10);
        *(s32 *)(S + 0x70) = *(s32 *)(s0 + 0x10);
        *(s32 *)(S + 0x74) = (s32)s2;
        t0v = *(s64 *)(S + 0x58);
        *(s32 *)(S + 0x78) = *(s32 *)(s1 + 0x360);
        a3v = *(s64 *)(S + 0x60);
        t3v = *(s64 *)(S + 0x40);
        *(s32 *)(S + 0x7C) = *(s32 *)(s1 + 0x364) + (*(s32 *)(s0 + 0x10) << 5);
        t2v = *(s64 *)(S + 0x48);
        v0v = *(s64 *)(S + 0x68);
        t1v = *(s64 *)(S + 0x50);
        v1v = *(s64 *)(S + 0x70);
        a2v = *(s64 *)(S + 0x78);
        *(s64 *)(S + 0x18) = t0v;
        *(s64 *)(S + 0x20) = a3v;
        *(s64 *)(S + 0x30) = v1v;
        *(s64 *)(S + 0x38) = a2v;
        *(s64 *)(S + 0x00) = t3v;
        *(s64 *)(S + 0x08) = t2v;
        *(s64 *)(S + 0x10) = t1v;
        *(s64 *)(S + 0x28) = v0v;
        func_00129C28((s32)(S + 0x10), (s32)(s0 + 0x90), a2v, a3v, t0v, t1v, t2v, t3v);
        func_00129C28((s32)(S + 0x20), (s32)(s0 + 0xB0));
        temp_v0 = EftRibbon_Create((s32)S);
        *(s32 *)(s0 + 0xD4) = temp_v0;
        EftRibbon_SetTexFrame(temp_v0, 0, (s32)s2, 0, *(s32 *)(s0 + 0x10));
        f0 = *(f32 *)(s0 + 0x6C) * D_00384EDC;
        if (!(*(s64 *)(D_003876A0 + 0x4D8) & 2)) {
            CVT_W_S(x, *(f32 *)(s0 + 0x6C) * D_00384EDC);
            c = (x < 3) ? 3 : ((x >= 0x11) ? 0x10 : x);
            EftRibbon_SetUnk5C(*(s32 *)(s0 + 0xD4), c);
        }
    }
    return f0;
}
