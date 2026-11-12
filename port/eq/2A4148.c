#include "common.h"

/* cvt.w.s with the FCSR default (truncates toward zero), written out: dst = (s32)x */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(dst, x) do { \
    (dst) = (s32)(x); \
} while (0)

s32 *func_002A3C08(s32 arg0);
void *func_002A3DB8(s32 arg0);
void func_002A4CF0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
    s32 a8, s32 a9, s32 a10, s32 a11, s32 a12, s32 a13, s32 a14, s32 a15, s32 a16);

void func_002A4148(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 s0 = arg2;
    s32 s1 = 0;
    s32 s2 = 0xC8;
    s32 r;
    s32 *p1;
    s32 *p2;
    f32 f0;
    f32 f1;

    if (arg0 >= -1) {
        if (arg0 > 0) {
            if (arg0 == 1) {
                s1 = 0x182;
                if (arg3 < 0x25) {
                    s2 = 0xC8;
                    f1 = (f32)arg3 / 37.0f;
                    f0 = 1.0f - f1;
                    f0 = f0 * 64.0f;
                    CVT_W_S(r, f0);
                    s1 = r + 0x182;
                }
            }
        } else {
            s1 = -2;
            if (arg3 < 0x25) {
                s2 = 0xC8;
                f1 = (f32)arg3 / 37.0f;
                f0 = 1.0f - f1;
                f0 = f0 * 64.0f;
                CVT_W_S(r, f0);
                s1 = -2 - r;
            }
        }
    }
    p1 = func_002A3C08(arg1);
    if (p1 == NULL) {
        /* slot sin buffer de texto: no dibujar el retrato (pagina cero no mapeada en el host) */
        *(u8 *)((u8 *)func_002A3DB8(0x1A) + 0x18) = 0;
        return;
    }
    s0 = (arg2 >= *p1) ? 0 : arg2;
    p2 = p1;
    func_002A4CF0(0x1A, 3, (s32)p2, s0, s1, s2, s1 + 0x80, s2 + 0x100,
        0x80, 0x80, 0x80, 0x80, 0, 0, 0x80, 0x100, 0);
}
