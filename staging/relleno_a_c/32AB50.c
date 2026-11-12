#include "common.h"

void std(u8 *fp, s32 flags, s32 file, u8 *data);

/* 0x0032AB50 __sinit (newlib findfp.c): s->__cleanup (+0x3C) = _cleanup_r (func_0032AB10, guardada con su
 * dirección PS2 como en std), s->__sdidinit (+0x38) = 1; stdin/stdout/stderr = s+0x1E4/0x23C/0x294 (FILE de
 * 0x58 bytes) con std(f, 4 = __SRD, 0, s), std(f, 9 = __SWR|__SLBF, 1, s), std(f, 0xA = __SWR|__SNBF, 2, s);
 * __sglue (+0x1D8) = {next 0, niobs 3, iobs s+0x1E4}. */
void __sinit(u8 *s) {
    u8 *iobs = s + 0x1E4;

    *(u32 *)(s + 0x3C) = 0x0032AB10u;
    *(s32 *)(s + 0x38) = 1;
    std(iobs, 4, 0, s);
    std(s + 0x23C, 9, 1, s);
    std(s + 0x294, 0xA, 2, s);
    *(s32 *)(s + 0x1D8) = 0;
    *(u8 **)(s + 0x1E0) = iobs;
    *(s32 *)(s + 0x1DC) = 3;
}
