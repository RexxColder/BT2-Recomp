#include "common.h"

extern void (*D_0034520C)(s32, s32) __attribute__((section(".data")));
extern s32 D_00345210 __attribute__((section(".data")));

s32 func_002B2738(s32 arg0) {
    if (D_0034520C != NULL) {
        D_0034520C(D_00345210, arg0);
    }
    return 0;
}
