#include "common.h"

void func_00191238(s32 arg0);

s32 func_00191688(u8 *arg0) {
    u8 *p;
    u8 *q;
    s32 v;

    if (arg0 == 0) {
        return 0;
    }
    p = (u8 *)*(s32 *)(arg0 + 0x28);
    if (*(s32 *)p != (s32)0x00191238u) {
        return 0;
    }
    q = (u8 *)*(s32 *)(arg0 + 0x38);
    v = *(s32 *)(q + 0x30);
    if ((v & 1) == 0) {
        return 0;
    }
    *(s32 *)(q + 0x30) = v | 0x2;
    return 1;
}
