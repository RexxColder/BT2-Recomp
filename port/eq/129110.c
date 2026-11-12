#include "common.h"
#include "vu0_state.h"

/* 0x00129110 Vu0Cur_Transpose: transposes the 4x4 word matrix in vf16..vf19 in place (same shuffle as the
 * sceVu0TransposeMatrix, vf[16 + j] word i = old vf[16 + i] word j). */
void func_00129110(void) {
    s32 m[16];
    s32 i;
    s32 j;
    s32 *w = (s32 *)&gVu0.vf[16][0];

    for (i = 0; i < 16; i++) {
        m[i] = w[i];
    }
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            w[j * 4 + i] = m[i * 4 + j];
        }
    }
}
