#include "common.h"

extern f32 D_00386EDC;

void func_002690C0(u32 *arg0, u32 arg1, u8 *arg2) {
    u32 *w;
    u32 *a3;
    u32 *t0;
    u32 *t7;
    u8 *a0;
    u8 *v1p;
    s32 t4;
    s32 t6;
    s32 t1;
    s32 i;
    s32 a0v;
    s32 v1v;
    s32 total;
    s32 rem;
    f32 f0;
    f32 f1;
    f32 scale;

    scale = D_00386EDC;

    /* first header, then the 0x4000-style fill of the GS packet */
    arg0[0] = 0x60000000;
    arg0[1] = 0;
    arg0[2] = 0x6C018000;
    arg0[3] = 0x8000;
    arg0[4] = 0x302EC000;
    arg0[5] = 0x412;
    arg0[6] = 0;
    arg0[7] = 0x17000000;
    a3 = arg0 + 8;
    t6 = 0;

    do {
        /* header words at w[0..14] */
        w = a3;
        w[0] = 0x6C038000;
        w[1] = 0x8001;
        w[2] = 0x10000000;
        w[3] = 6;
        w[4] = 0;
        w[5] = 0;
        w[6] = 0;
        w[7] = 0;
        w[8] = 0;
        w[9] = 0;
        t7 = w + 10;
        w[11] = 0x302E4000;
        w[12] = 0x412;
        t4 = 0;
        w[13] = 0;
        w[14] = 0;
        t0 = w + 15;
        a0 = arg2 + 64 * t6;

        /* block loop: three vectors per block, t4 counts the blocks of this header */
        do {
            v1p = a0;
            for (i = 0; i < 3; i++) {
                f0 = *(f32 *)(v1p + 0x30) * scale;
                f0 = *(f32 *)(a0 + 0x0) + f0;
                *(f32 *)t0 = f0;
                t0 += 1;
                f1 = *(f32 *)(v1p + 0x34) * scale;
                f1 = *(f32 *)(a0 + 0x4) + f1;
                *(f32 *)t0 = f1;
                t0 += 1;
                a3 = t0 + 1;
                f0 = *(f32 *)(v1p + 0x38) * scale;
                f1 = *(f32 *)(a0 + 0x8) + f0;
                a0 += 0x10;
                *(f32 *)t0 = f1;
                if (i < 2) {
                    a3[0] = (t4 != 0) ? 1 : 0;
                } else {
                    a3[0] = 0;
                }
                a3 += 1;
                t0 = a3 + 12;
                *(f32 *)(a3 + 0) = *(f32 *)(v1p + 0x30);
                *(f32 *)(a3 + 1) = *(f32 *)(v1p + 0x34);
                *(f32 *)(a3 + 3) = 1.0f;
                *(f32 *)(a3 + 2) = *(f32 *)(v1p + 0x38);
                *(f32 *)(a3 + 4) = *(f32 *)(v1p + 0xC);
                *(f32 *)(a3 + 5) = *(f32 *)(v1p + 0xC);
                *(f32 *)(a3 + 7) = 128.0f;
                *(f32 *)(a3 + 6) = *(f32 *)(v1p + 0xC);
                a3[8] = 0;
                a3[9] = 0;
                *(f32 *)(a3 + 10) = 1.0f;
                a3[11] = 0;
            }
            t6 += 1;
            t1 = ((s32)t6 < (s32)arg1);
            t4 += 1;
            if (t1 == 0) {
                break;
            }
            a0 = arg2 + 64 * t6;
        } while (t4 < 0x12);

        /* packet tail for this header */
        a0v = t4 * 3;
        v1v = (s32)((u32)a0v << 18) | 0x6C008003;
        a0v = a0v | 0x8000;
        a3 = t0;
        t7[4] = (u32)v1v;
        t7[0] = (u32)a0v;
        a3[0] = 0x17000000;
        a3 += 1;
    } while (t1 != 0);

    /* pad to a multiple of four words with zeros */
    total = (s32)(a3 - arg0);
    rem = total & 3;
    if (rem != 0) {
        s32 k = 4 - rem;
        do {
            a3[0] = 0;
            a3 += 1;
            k -= 1;
        } while (k != 0);
    }

    a3[0] = 0x70000000;
    a3[1] = 0;
    a3[2] = 0;
    a3[3] = 0;
    a3 += 4;

    total = (s32)(a3 - arg0);
    arg0[0] = 0x5FFFFFFE + (u32)(total >> 2);
}
