#include "common.h"

s32 func_00126698(void *arg0, s32 arg1);
void func_0027B198(s32 arg0, s32 arg1);
void func_0027B430(s32 arg0, s32 arg1);
extern u8 *D_003876A0;
extern u8 *D_00387AEC;

/* 0x0027BBA0: per-frame update of the record at D_00387AEC (flags word at +0xA4; counts at
 * +0xA8 and +0xAC). Sets flag bits 1/2/4 from the counts when the 64-bit word at D_003876A0+0x4D8
 * has bit 1 set (else just bit 1), then dispatches the flags to func_0027B198/func_0027B430 and
 * clears the flags word. */
void func_0027BBA0(void) {
    u8 *p = D_00387AEC;
    s32 a1;
    s32 flags;

    if (p == NULL) {
        return;
    }
    a1 = *(s32 *)(p + 0xA8);
    if (a1 + *(s32 *)(p + 0xAC) == 0) {
        return;
    }

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 2) == 0) {
        *(s32 *)(p + 0xA4) |= 1;
    } else {
        if (a1 != 0) {
            *(s32 *)(p + 0xA4) |= 2;
        }
        if (*(s32 *)(p + 0xAC) != 0) {
            *(s32 *)(p + 0xA4) |= 4;
        }
        if (func_00126698(p, a1) != 0) {
            *(s32 *)(D_00387AEC + 0xA4) = 1;
        }
    }

    flags = *(s32 *)(D_00387AEC + 0xA4);
    if ((flags & 1) != 0) {
        func_0027B198(0, 0);
        func_0027B430(0, 0);
    } else {
        if ((flags & 2) != 0) {
            func_0027B198(1, 0);
            func_0027B430(1, 0);
        }
        if ((*(s32 *)(D_00387AEC + 0xA4) & 4) != 0) {
            func_0027B198(1, 1);
            func_0027B430(1, 1);
        }
    }
    *(s32 *)(D_00387AEC + 0xA4) = 0;
}
