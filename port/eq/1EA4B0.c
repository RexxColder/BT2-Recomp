#include "common.h"

void func_001EA4B0(void **arg0, void **arg1, u8 *arg2) {
    u8 *v1;
    u8 *v0;
    u8 *a2;

    if (*arg0 != NULL) {
        v1 = *(u8 **)(arg2 + 0x1C);
        if (v1 != NULL) {
            v0 = *(u8 **)(arg2 + 0x18);
            if (v0 == NULL) {
                *arg1 = v1;
                *(void **)(v1 + 0x18) = NULL;
                return;
            }
            *(u8 **)(v0 + 0x1C) = v1;
            *(u8 **)(v1 + 0x18) = v0;
        } else {
            a2 = *(u8 **)(arg2 + 0x18);
            if (a2 != NULL) {
                *arg0 = a2;
                *(void **)(a2 + 0x1C) = NULL;
                return;
            }
            *arg0 = NULL;
            *arg1 = NULL;
        }
    }
}
