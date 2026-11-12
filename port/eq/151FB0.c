#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

s32 EftRay_IsAlive(s32 arg0);
s32 func_001CCA88(s32 arg0);
s32 EftRibbon_IsAlive(s32 arg0);
s32 func_001A48F8(s32 arg0);
s32 EftPtcl4_IsAlive(s32 arg0);
void func_001E7178(u8 *arg0);
s32 func_0018E558(s32 arg0);
s32 EftChain2_IsAlive(s32 arg0);
s32 func_00190A70(s32 arg0);
s32 EftPtcl3_IsAlive(s32 arg0);
s32 func_0018C0F0(s32 arg0);
s32 func_00194E30(s32 arg0);

void func_00151FB0(u8 *arg0) {
    u8 *s3;
    u8 *s4;
    s32 s5;
    s32 k;
    s32 v;
    s32 off;

    s3 = arg0 + 0xE4;
    s5 = 0;
    do {
        s4 = s3 + 4;

        for (k = 0; k < 8; k++) {
            off = 0x200 + 8 * k;
            v = W(s3, off);
            if (v >= 0 && v < 2) {
                if (EftRay_IsAlive(W(s4, off)) == 0) {
                    W(s4, off) = 0;
                }
            }
        }

        for (k = 0; k < 8; k++) {
            off = 0x240 + 4 * k;
            if (func_001CCA88(W(s4, off)) == 0) {
                W(s4, off) = 0;
            }
        }

        if (EftRibbon_IsAlive(W(s3, 0x264)) == 0) {
            W(s3, 0x264) = 0;
        }
        if (func_001A48F8(W(s3, 0x268)) == 0) {
            W(s3, 0x268) = 0;
        }

        for (k = 0; k < 8; k++) {
            off = 0x26C + 4 * k;
            if (EftPtcl4_IsAlive(W(s3, off)) == 0) {
                W(s3, off) = 0;
            }
        }

        for (k = 0; k < 7; k++) {
            func_001E7178(s3 + 0x28C + 4 * k);
        }

        for (k = 0; k < 5; k++) {
            off = 0x2A8 + 4 * k;
            if (func_0018E558(W(s3, off)) == 0) {
                W(s3, off) = 0;
            }
        }

        for (k = 0; k < 5; k++) {
            off = 0x2B0 + 0xC + 4 * k;
            if (EftChain2_IsAlive(W(s3, off)) == 0) {
                W(s3, off) = 0;
            }
        }

        for (k = 0; k < 5; k++) {
            off = 0x2D0 + 4 * k;
            if (func_00190A70(W(s3, off)) == 0) {
                W(s3, off) = 0;
            }
        }

        for (k = 0; k < 8; k++) {
            off = 0x2E0 + 4 * k;
            if (EftPtcl3_IsAlive(W(s4, off)) == 0) {
                W(s4, off) = 0;
            }
        }

        for (k = 0; k < 8; k++) {
            off = 0x300 + 4 * k;
            if (EftPtcl3_IsAlive(W(s4, off)) == 0) {
                W(s4, off) = 0;
            }
        }

        for (k = 0; k < 4; k++) {
            off = 0x320 + 4 * k;
            if (func_0018C0F0(W(s4, off)) == 0) {
                W(s4, off) = 0;
            }
        }

        for (k = 0; k < 8; k++) {
            off = 0x330 + 4 * k;
            if (func_00194E30(W(s4, off)) == 0) {
                W(s4, off) = 0;
            }
        }

        s5 += 1;
        s3 += 0x364;
    } while (s5 < 2);
}
