#include "common.h"

/* Decodes a 27-byte scrambled code block (bit-permuted fields, checksum bits, parity) into 16 s16 values.
   Returns 0 on success, -1 on any validation failure. */

#define BIT(x, n) (((x) >> (n)) & 1)

s32 func_003BCD00(s16 *out, u8 *in) {
    u32 b4 = in[4], b5 = in[5], b6 = in[6], b7 = in[7], b8 = in[8], b9 = in[9];
    u32 b10 = in[10], b11 = in[11], b12 = in[12], b13 = in[13], b14 = in[14];
    u32 b15 = in[15], b16 = in[16], b17 = in[17], b18 = in[18], b19 = in[19];
    u32 b20 = in[20], b21 = in[21], b22 = in[22], b23 = in[23], b24 = in[24];
    u32 b25 = in[25], b26 = in[26];
    s16 f[7];
    u32 mask1, mask2, stored;
    s32 parity, i, j;
    s32 v1, v2, v3, v4, v5, v6, v7, v8, sum;
    s16 w3;

    /* first checksum mask */
    mask1 = (BIT(b4, 6) << 31) | (BIT(b4, 0) << 28) | (BIT(b4, 2) << 29) | (BIT(b4, 4) << 30)
          | (BIT(b5, 6) << 27) | (BIT(b5, 3) << 26) | (BIT(b6, 2) << 23) | (BIT(b6, 5) << 24)
          | (BIT(b5, 0) << 25) | (BIT(b6, 0) << 22) | (BIT(b7, 7) << 21) | (BIT(b7, 1) << 19)
          | (BIT(b7, 4) << 20) | (BIT(b8, 5) << 18) | (BIT(b8, 0) << 16) | (BIT(b8, 3) << 17)
          | (BIT(b9, 6) << 15) | (BIT(b9, 2) << 13) | (BIT(b9, 5) << 14)
          | (BIT(b10, 7) << 12) | (BIT(b10, 1) << 10) | (BIT(b10, 4) << 11)
          | (BIT(b11, 6) << 9) | (BIT(b11, 0) << 7) | (BIT(b11, 3) << 8)
          | (BIT(b12, 7) << 6) | (BIT(b12, 2) << 4) | (BIT(b12, 5) << 5)
          | (BIT(b13, 7) << 3) | (BIT(b13, 1) << 1) | (BIT(b13, 4) << 2)
          | BIT(b14, 5);

    stored = ((u32)in[0] << 24) | ((u32)in[1] << 16) | ((u32)in[2] << 8) | in[3];

    /* seven 10-bit fields later stored as value - 300 */
    f[0] = (BIT(b14, 7) << 9) | (BIT(b15, 5) << 2) | (BIT(b14, 3) << 6) | (BIT(b14, 0) << 4)
         | (BIT(b14, 6) << 8) | (BIT(b14, 4) << 7) | (BIT(b14, 1) << 5) | (BIT(b15, 6) << 3)
         | (BIT(b15, 3) << 1) | BIT(b15, 2);
    f[1] = (BIT(b15, 0) << 9) | (BIT(b17, 7) << 2) | (BIT(b16, 4) << 6) | (BIT(b16, 1) << 4)
         | (BIT(b16, 7) << 8) | (BIT(b16, 5) << 7) | (BIT(b16, 3) << 5) | (BIT(b16, 0) << 3)
         | (BIT(b17, 5) << 1) | BIT(b17, 4);
    f[2] = (BIT(b17, 3) << 9) | (BIT(b18, 1) << 2) | (BIT(b18, 7) << 6) | (BIT(b18, 4) << 4)
         | (BIT(b17, 1) << 8) | (BIT(b17, 0) << 7) | (BIT(b18, 5) << 5) | (BIT(b18, 3) << 3)
         | (BIT(b18, 0) << 1) | BIT(b19, 7);
    f[3] = (BIT(b19, 5) << 9) | (BIT(b20, 3) << 2) | (BIT(b19, 1) << 6) | (BIT(b20, 6) << 4)
         | (BIT(b19, 4) << 8) | (BIT(b19, 3) << 7) | (BIT(b19, 0) << 5) | (BIT(b20, 5) << 3)
         | (BIT(b20, 2) << 1) | BIT(b20, 0);
    f[4] = (BIT(b22, 0) << 9) | (BIT(b24, 7) << 2) | (BIT(b23, 4) << 6) | (BIT(b23, 1) << 4)
         | (BIT(b23, 7) << 8) | (BIT(b23, 5) << 7) | (BIT(b23, 3) << 5) | (BIT(b23, 0) << 3)
         | (BIT(b24, 5) << 1) | BIT(b24, 4);
    f[5] = (BIT(b21, 7) << 9) | (BIT(b22, 5) << 2) | (BIT(b21, 3) << 6) | (BIT(b21, 0) << 4)
         | (BIT(b21, 6) << 8) | (BIT(b21, 4) << 7) | (BIT(b21, 1) << 5) | (BIT(b22, 6) << 3)
         | (BIT(b22, 3) << 1) | BIT(b22, 2);
    f[6] = (BIT(b24, 2) << 9) | (BIT(b25, 0) << 2) | (BIT(b25, 6) << 6) | (BIT(b25, 3) << 4)
         | (BIT(b24, 1) << 8) | (BIT(b25, 7) << 7) | (BIT(b25, 4) << 5) | (BIT(b25, 2) << 3)
         | (BIT(b26, 7) << 1) | BIT(b26, 6);

    if (stored != ~mask1) {
        return -1;
    }

    /* second checksum mask */
    mask2 = (BIT(b14, 2) << 31) | (BIT(b15, 4) << 29) | (BIT(b15, 7) << 30) | (BIT(b15, 1) << 28)
          | (BIT(b16, 2) << 26) | (BIT(b16, 6) << 27) | (BIT(b17, 6) << 25) | (BIT(b17, 2) << 24)
          | (BIT(b18, 2) << 22) | (BIT(b18, 6) << 23) | (BIT(b19, 6) << 21) | (BIT(b19, 2) << 20)
          | (BIT(b20, 4) << 18) | (BIT(b20, 7) << 19) | (BIT(b20, 1) << 17) | (BIT(b21, 5) << 16)
          | (BIT(b22, 7) << 14) | (BIT(b21, 2) << 15) | (BIT(b22, 4) << 13) | (BIT(b22, 1) << 12)
          | (BIT(b23, 2) << 10) | (BIT(b23, 6) << 11) | (BIT(b24, 6) << 9)
          | (BIT(b24, 3) << 8) | (BIT(b26, 2) << 1) | (BIT(b25, 1) << 5) | (BIT(b26, 4) << 3)
          | (BIT(b24, 0) << 7) | (BIT(b25, 5) << 6)
          | (BIT(b26, 5) << 4) | (BIT(b26, 3) << 2) | BIT(b26, 1);

    if (stored != ~mask2) {
        return -1;
    }

    /* parity over all 27 bytes must be even */
    parity = 0;
    for (i = 0; i < 27; i++) {
        for (j = 0; j < 8; j++) {
            parity += (in[i] >> j) & 1;
        }
    }
    if (parity & 1) {
        return -1;
    }

    /* 5-bit fields (biased by 7) */
    v2 = (s16)(((BIT(b7, 6) << 4) | BIT(b7, 0) | (BIT(b7, 3) << 2) | (BIT(b7, 5) << 3) | (BIT(b7, 2) << 1)) - 7);
    v4 = (s16)(((BIT(b9, 7) << 4) | BIT(b9, 0) | (BIT(b9, 3) << 2) | (BIT(b9, 4) << 3) | (BIT(b9, 1) << 1)) - 7);
    v5 = (s16)(((BIT(b10, 6) << 4) | BIT(b10, 0) | (BIT(b10, 3) << 2) | (BIT(b10, 5) << 3) | (BIT(b10, 2) << 1)) - 7);
    v6 = (s16)(((BIT(b11, 7) << 4) | BIT(b11, 1) | (BIT(b11, 4) << 2) | (BIT(b11, 5) << 3) | (BIT(b11, 2) << 1)) - 7);
    v8 = (s16)(((BIT(b13, 6) << 4) | BIT(b13, 0) | (BIT(b13, 3) << 2) | (BIT(b13, 5) << 3) | (BIT(b13, 2) << 1)) - 7);
    v7 = (s16)(((BIT(b12, 6) << 4) | BIT(b12, 0) | (BIT(b12, 3) << 2) | (BIT(b12, 4) << 3) | (BIT(b12, 1) << 1)) - 7);
    v3 = (s16)(((BIT(b8, 7) << 4) | BIT(b8, 1) | (BIT(b8, 4) << 2) | (BIT(b8, 6) << 3) | (BIT(b8, 2) << 1)) & 0xFFFF);
    v1 = (s16)(((BIT(b5, 4) << 7) | BIT(b6, 1) | (BIT(b6, 7) << 4) | (BIT(b6, 4) << 2)
              | (BIT(b5, 2) << 6) | (BIT(b5, 1) << 5) | (BIT(b6, 6) << 3) | (BIT(b6, 3) << 1)) - 7);

    sum = v2 + v8 + v3 + v6 + v5 + v4 + v7;
    if (v1 != sum) {
        return -1;
    }

    w3 = (s16)(((BIT(b4, 7) << 5) | BIT(b5, 5) | (BIT(b4, 1) << 2) | (BIT(b4, 3) << 3)
              | (BIT(b4, 5) << 4) | (BIT(b5, 7) << 1)) - 7);

    out[15] = f[6] - 300;
    out[0] = w3;
    out[1] = v1;
    out[2] = v2;
    out[3] = v3;
    out[4] = v4;
    out[5] = v5;
    out[6] = v6;
    out[7] = v7;
    out[8] = v8;
    out[9] = f[0] - 300;
    out[10] = f[1] - 300;
    out[11] = f[2] - 300;
    out[12] = f[3] - 300;
    out[13] = f[5] - 300;
    out[14] = f[4] - 300;
    return 0;
}
