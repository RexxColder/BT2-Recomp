#include "common.h"

#define W32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))
/* cvt.w.s on the EE: truncates toward zero and saturates. */
#define CVT_W(x) (((x) >= 2147483648.0f) ? 0x7FFFFFFF : (((x) < -2147483648.0f) ? (-2147483647 - 1) : (s32)(x)))
/* the game's unsigned-range trick: values >= 2^31 keep bit 31 set (the `or` with s4). */
#define CVT_U(x) (((x) >= 2147483648.0f) ? (s32)((u32)CVT_W((x) - 2147483648.0f) | 0x80000000u) : CVT_W(x))

extern u8 D_0036E9F0[];

void *memcpy(void *d, const void *s, u32 n);
void func_001F0418(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10);

void func_001A1FF0(u8 *obj) {
    u8 sp[0x80];
    u8 *s1 = sp + 0x20;
    u8 *E;
    s32 s3;

    memcpy(s1, D_0036E9F0, 0x30);

    s3 = 7;
    E = obj + 0x30;
    while (s3 >= 0) {
        if ((W32(E, 0x48) & 1) && !(W32(E, 0x4C) > 0)) {
            s32 a3v = CVT_U(F32(E, 0x20) * 128.0f) & 0xFF;
            s32 t3v = CVT_U(F32(E, 0x34) * 4096.0f);
            u8 *p1 = s1 + (W32(E, 0x44) << 4);
            s32 v3 = W32(obj, 0x330) + (W32(E, 0x50) << 4);

            func_001F0418(F32(E, 0x0), F32(E, 0x4), F32(E, 0x8), F32(p1, 0x0), F32(p1, 0x4), F32(p1, 0x8),
                          F32(p1, 0xC), F32(E, 0x2C),
                          0x80, 0x80, 0x80, a3v, 0x20, 0x20, 0, t3v,
                          0, W32(E, 0x54), v3);
        }
        s3--;
        E += 0x60;
    }
}
