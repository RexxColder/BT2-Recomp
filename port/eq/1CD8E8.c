#include "common.h"

void EftPtcl3_Stop(s32 arg0);

void func_001CD8E8(u8 *arg0) {
    u8 *s2 = *(u8 **)(arg0 + 0x38);
    s32 s3 = 0;

    do {
        u8 *p = s2 + 0x10;
        s32 a0 = *(s32 *)p;
        s32 s1 = 1;

        do {
            p += 4;
            s1 -= 1;
            EftPtcl3_Stop(a0);
            if (s1 >= 0) {
                a0 = *(s32 *)p;
            }
        } while (s1 >= 0);
        s3 += 1;
        s2 += 8;
    } while (s3 < 2);
}
