#include "common.h"

extern void (*D_0035532C)(s32) __attribute__((section(".data")));
extern s32 D_00355330 __attribute__((section(".data")));

void _sceCd_Poff_Intr(void) {
    if (D_0035532C != NULL) {
        D_0035532C(D_00355330);
    }
}
