#include "common.h"

extern u8 *D_003879A0;

void func_0024CF40(void) {
    s32 v = *(s32 *)(D_003879A0 + 0x1C4);

    if (!(v & 0x40)) {
        *(s32 *)(D_003879A0 + 0x3224) = 5;
    } else {
        *(s32 *)(D_003879A0 + 0x1C4) = v ^ 0x40;
    }
    *(s32 *)(D_003879A0 + 0x1C4) = *(s32 *)(D_003879A0 + 0x1C4) | 1;
}
