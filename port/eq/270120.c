#include "common.h"

/* 0x00270120(dst, src1, src2): when src1 != NULL, 24 bytes of src1 go to dst + 0x78; when src2 != NULL, 24 bytes of
 * src2 go to dst + 0x90. */
void func_00270120(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 k;

    if (arg1 != 0) {
        for (k = 0; k < 24; k++) {
            arg0[0x78 + k] = arg1[k];
        }
    }
    if (arg2 != 0) {
        for (k = 0; k < 24; k++) {
            arg0[0x90 + k] = arg2[k];
        }
    }
}
