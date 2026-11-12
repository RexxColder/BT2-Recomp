#include "common.h"

void func_001C9388(void *arg0, void *arg1, void *arg2);
extern u8 *D_003878B4;

void func_001C9510(s32 arg0) {
    u8 *s0;
    u8 *head;
    u8 *v1;

    s0 = *(u8 **)(D_003878B4 + 0x120);
    while (s0 != NULL) {
        if (*(s32 *)(s0 + 4) == arg0) {
            head = *(u8 **)s0;
            if (head == NULL) {
                *(u8 **)s0 = NULL;
                *(s32 *)(s0 + 8) = 0;
                func_001C9388(D_003878B4 + 0x120, D_003878B4 + 0x124, s0);
            } else {
                v1 = *(u8 **)(head + 0x38);
                if (v1 == NULL) {
                    return;
                }
                *(s32 *)(v1 + 0x94) = *(s32 *)(v1 + 0x94) | 2;
                *(u8 **)s0 = NULL;
                *(s32 *)(s0 + 8) = 0;
                func_001C9388(D_003878B4 + 0x120, D_003878B4 + 0x124, s0);
                return;
            }
        }
        s0 = *(u8 **)(s0 + 0xC);
    }
}
