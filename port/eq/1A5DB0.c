#include "common.h"

void EftPtcl3_Stop(s32 arg0);

void func_001A5DB0(u8 *arg0) {
    u8 *s0;
    u8 *v;
    s32 i;
    s32 a0;

    if (*(s32 *)(arg0 + 0x10) == 0) {
        return;
    }
    if (*(s32 *)(arg0 + 0x14) == 0) {
        return;
    }
    v = *(u8 **)(arg0 + 0xC);
    if (v == NULL) {
        return;
    }
    if (*(s32 *)(v + 0x100) == 0) {
        return;
    }
    if (*(s32 *)(arg0 + 0x68) <= 0) {
        return;
    }
    i = 0;
    s0 = arg0;
    do {
        a0 = *(s32 *)s0;
        s0 += 4;
        i += 1;
        EftPtcl3_Stop(a0);
    } while (i < *(s32 *)(arg0 + 0x68));
}
