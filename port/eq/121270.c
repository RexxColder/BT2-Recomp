#include "common.h"

f32 sinf(f32 arg0);
f32 cosf(f32 arg0);
extern f32 D_003840A4;
extern f32 D_003840A8;
extern f32 D_003840AC;
extern f32 D_003840B0;
extern f32 D_003840B4;
extern f32 D_003840B8;

/* 0x00121270: updates the float pair at arg0+0x10 (x) and arg0+0x1C (w): x += D_003840A4, w = w + (k * D_003840A8 (k =
 * word +8 + 1)) and sin(x) terms (see the asm), then w = w - D_003840B8 when w > D_003840B4. Then the two bytes at
 * arg0+0 and +1 are clamp(255 * (0.5 + 0.5 cos w)) and clamp(255 * (0.5 - 0.5 sin w)). */
void func_00121270(u8 *arg0) {
    f32 *q = (f32 *)(arg0 + 0x10);
    f32 a;
    f32 b;
    f32 f3;
    f32 cc;
    f32 nsn;
    s32 i0;
    s32 i1;

    q[0] += D_003840A4;
    a = (f32)(*(s32 *)(arg0 + 0x8) + 1) * D_003840A8;
    b = sinf(q[0]) * 0.5f + 0.5f;
    b = b * D_003840AC;
    a = a + b;
    a = a * D_003840B0;
    f3 = q[3] + a;
    if (D_003840B4 < f3) {
        q[3] = f3 - D_003840B8;
    }
    cc = cosf(q[3]) * 0.5f + 0.5f;
    nsn = -sinf(q[3]) * 0.5f + 0.5f;
    cc = cc * 255.0f;
    nsn = nsn * 255.0f;
    i0 = (s32)cc;
    if (i0 < 0) {
        i0 = 0;
    }
    if (i0 >= 0x100) {
        i0 = 0xFF;
    }
    arg0[0] = (u8)i0;
    i1 = (s32)nsn;
    if (i1 < 0) {
        i1 = 0;
    }
    if (i1 >= 0x100) {
        i1 = 0xFF;
    }
    arg0[1] = (u8)i1;
}
