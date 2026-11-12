#include "common.h"

void func_001BCEE0(s32 arg0, s32 arg1, s32 arg2);
s32 rand(void);
extern void *gEftPtcl4Mgr;

void func_001BDE48(u8 *arg0, u8 *arg1) {
    u8 *s2;
    u8 *mgr;
    s32 s0;
    s32 s1;
    s32 s3;
    u8 b8;
    f32 f;

    s1 = 0;
    s2 = *(u8 **)(arg1 + 0x38);
    if (*(f32 *)(arg0 + 0x74) <= 0.0f) {
        do {
            mgr = gEftPtcl4Mgr;
            s0 = 0xC8 - *(s32 *)(mgr + 8);
            s3 = 0;
            if (s0 > 0) {
                s1 = s2[6];
                if (s2[7] != 0) {
                    s1 += rand() % (s32)s2[7];
                }
                b8 = s2[8];
                if (b8 != 0) {
                    if ((s32)b8 < s0) {
                        s3 = 1;
                        if (s0 < s1 + (b8 + s1)) {
                            s1 = s0 / (s32)(b8 + 1);
                            s3 = 1;
                        }
                    }
                } else {
                    s3 = 1;
                    if (s0 < s1) {
                        s1 = s0;
                    }
                }
            }
            if (s3 != 0) {
                func_001BCEE0((s32)arg0, (s32)arg1, s1);
            }
            f = *(f32 *)(arg0 + 0x74) + *(f32 *)(s2 + 0xC);
            *(f32 *)(arg0 + 0x74) = f;
        } while ((s3 != 0) && (f <= 0.0f));
    }
}
