#include "common.h"

void func_00269A40(s32 arg0, s32 arg1);

/* 0x002642D0: walks the list at arg0 + 0x48 (each node's first word is the step to the next node): calls
 * func_00269A40(arg0, node->0xA as u16) for the node, and moves on while node->0x6 (u16) is 0. */
void func_002642D0(u8 *arg0) {
    u8 *s0 = *(u8 **)(arg0 + 0x48);

    for (;;) {
        func_00269A40((s32)arg0, *(u16 *)(s0 + 0xA));
        if (*(u16 *)(s0 + 0x6) != 0) {
            return;
        }
        s0 = s0 + *(s32 *)s0;
    }
}
