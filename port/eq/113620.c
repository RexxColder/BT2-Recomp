#include "common.h"

void func_00112818(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void *memset(void *dst, s32 val, u32 n);

void func_00113620(u8 *arg0, s32 arg1) {
    f32 sp[16];
    f32 f20;
    f32 f21;
    s32 ix;
    s32 iy;
    s32 i;
    s16 a3;
    u8 *p;

    memset(sp, 0, 0x40);
    a3 = *(s16 *)(arg0 + 6);
    f20 = (f32)(*(s16 *)(arg0 + 8) - *(s16 *)(arg0 + 4)) * 0.5f;
    f21 = (f32)(*(s16 *)(arg0 + 0xA) - a3) * 0.5f;
    sp[0] = -f20;
    sp[1] = -f21;
    sp[3] = 1.0f;
    sp[4] = f20;
    sp[5] = -f21;
    sp[7] = 1.0f;
    sp[8] = -f20;
    sp[9] = f21;
    sp[11] = 1.0f;
    sp[12] = f20;
    sp[13] = f21;
    sp[15] = 1.0f;
    func_00112818((s32)(arg0 + 0x20), (s32)sp, 4, a3);

    if (arg1 == 1) {
        /* cvt.w.s truncates toward zero (saturating): plain cast of f20 */
        ix = (s32)f20;
        /* cvt.w.s truncates toward zero (saturating): plain cast of f21 */
        iy = (s32)f21;

        p = arg0 + 0x24;
        i = 3;
        do {
            i -= 1;
            *(s32 *)(p - 4) = *(s32 *)(p - 4) + (*(s16 *)(arg0 + 4) + ix);
            *(s32 *)(p + 0) = *(s32 *)(p + 0) + (*(s16 *)(arg0 + 6) + iy);
            p += 0x10;
        } while (i >= 0);
    }
    *(s32 *)arg0 = *(s32 *)arg0 | (s32)0x80000000;
}
