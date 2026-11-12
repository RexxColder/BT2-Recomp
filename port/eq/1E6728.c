#include "common.h"

void func_001E0B38(s32 arg0, s32 arg1);
void func_001E1BB0(s32 arg0, s32 arg1);

void func_001E6728(u8 *arg0, s32 arg1) {
    u8 *s0;
    s32 kind;

    if (arg0 == NULL) {
        return;
    }
    s0 = *(u8 **)(arg0 + 0x38);
    if ((*(s64 *)s0 & 5) != 1) {
        return;
    }
    if (*(s32 *)s0 & 2) {
        return;
    }
    kind = *(s32 *)(s0 + 8);
    if (kind == 0) {
        func_001E1BB0(*(s32 *)(s0 + 0x40), arg1);
    } else if (kind == 1) {
        func_001E0B38(*(s32 *)(s0 + 0x44), arg1);
    }
    *(s32 *)s0 = *(s32 *)s0 | 2;
}
