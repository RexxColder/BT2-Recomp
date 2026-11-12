#include "common.h"

s32 func_002EA050(void *a0, s32 a1, s32 a2, f32 f12);
void func_002F2BD8(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_0037CAA0 __attribute__((section(".data")));

void adxt_SetReloadTime(void *arg0, s32 arg1, s32 arg2, f32 f12) {
    f32 x;
    s32 t;
    s32 q;
    s32 w;
    s32 u;
    s32 a3;
    s32 a2v;

    if (arg0 == NULL) {
        func_002EA050(&D_0037CAA0, arg1, arg2, f12);
        return;
    }
    x = f12 * (f32)arg2;
    /* cvt.w.s truncates toward zero (saturating): plain cast */
    t = (s32)x;
    q = (t < 0 ? t + 31 : t) >> 5;
    q = (s32)((u32)q * (u32)arg1);
    w = (s32)((u32)q * 18u);
    u = (w < 0 ? w + 0x7FF : w) >> 11;
    a3 = *(s16 *)((u8 *)arg0 + 0x3C);
    a2v = (s32)((u32)a3 << 11);
    if (u < a3) {
        a3 = u;
    }
    *(s16 *)((u8 *)arg0 + 0x3E) = (s16)a3;
    if (*(s32 *)((u8 *)arg0 + 8) != 0) {
        func_002F2BD8(*(s32 *)((u8 *)arg0 + 8), (s32)((u32)a3 << 16) >> 5, a2v, a3);
    }
}
