#include "common.h"

s32 Queue_Pop(u8 *arg0) {
    u8 *v1 = *(u8 **)(arg0 + 0xC);
    u8 *a1;
    s32 v0 = 0;

    if (v1 != NULL) {
        a1 = *(u8 **)(v1 + 0);
        if (a1 != NULL) {
            *(u8 **)(arg0 + 0xC) = a1;
        } else {
            *(u8 **)(arg0 + 0xC) = NULL;
        }
        *(u8 **)(v1 + 0) = *(u8 **)(arg0 + 8);
        *(u8 **)(arg0 + 8) = v1;
        v0 = *(s32 *)(v1 + 4);
    }
    return v0;
}
