#include "common.h"

void func_001C9688(u8 *arg0) {
    u8 *v = *(u8 **)(arg0 + 0);
    u8 *nx;

    if (v != NULL) {
        do {
            nx = *(u8 **)(v + 0x130);
            *(s32 *)v = 0;
            v = nx;
        } while (v != NULL);
    }
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 0) = 0;
}
