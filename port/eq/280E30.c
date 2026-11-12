#include "common.h"

extern u8 *D_00387AFC;
extern u8 *D_003876A0;
void func_00281F88(s32 arg0);
void func_0027E9F0(s32 arg0);

/* 0x00280E30: unless D_00387AFC + 0x3CCA is non-zero: clear byte +0x3CC0, func_00281F88(D_00387AFC + 0x2F00); then
 * unless (D_003876A0 + 0x4D8 as s64) & 0x100 or D_003876A0 + 4 is 0: func_0027E9F0(D_00387AFC + 0x1600). */
void func_00280E30(void) {
    if (*(u8 *)(D_00387AFC + 0x3CCA) != 0) {
        return;
    }
    *(u8 *)(D_00387AFC + 0x3CC0) = 0;
    func_00281F88((s32)(D_00387AFC + 0x2F00));
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return;
    }
    if (*(s32 *)(D_003876A0 + 0x4) == 0) {
        return;
    }
    func_0027E9F0((s32)(D_00387AFC + 0x1600));
}
