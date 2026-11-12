#include "common.h"

void EftPtcl3_SetPos(s32 arg0, s32 arg1);
void EftPtcl3_SetDir(s32 arg0, s32 arg1);

void func_0019B078(u8 *arg0) {
    s32 base = *(s32 *)(arg0 + 0x38);
    s32 *p = (s32 *)(base + 0x10);
    s32 s1 = 2;

    do {
        s1 -= 1;
        EftPtcl3_SetPos(*p, base + 0x30);
        EftPtcl3_SetDir(*p, base + 0x40);
        p += 1;
    } while (s1 >= 0);
}
