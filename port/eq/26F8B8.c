#include "common.h"

/* 0x0026F8B8(dst, src1, src2): when src1 != NULL, 24 bytes of src1 go to dst + 8; when src2 != NULL, 24 bytes of
 * src2 go to dst + 0x20. */
void func_0026F8B8(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 k;

    if (arg1 != 0) {
        for (k = 0; k < 24; k++) {
            arg0[8 + k] = arg1[k];
        }
    }
    if (arg2 != 0) {
        for (k = 0; k < 24; k++) {
            arg0[0x20 + k] = arg2[k];
        }
    }
}
