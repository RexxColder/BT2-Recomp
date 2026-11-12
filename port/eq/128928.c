#include "common.h"

/* 0x00128928 sceVu0TransposeMatrix (VU0/EE pextlw/pextuw/pcpyld/pcpyud shuffle): a0[j][i] = a1[i][j] on 4x4 words.
 * The input is read whole first, so a0 may alias a1. */
void sceVu0TransposeMatrix(s32 *arg0, s32 *arg1) {
    s32 m[16];
    s32 i;
    s32 j;

    for (i = 0; i < 16; i++) {
        m[i] = arg1[i];
    }
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            arg0[j * 4 + i] = m[i * 4 + j];
        }
    }
}
