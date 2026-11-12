#include "common.h"

void func_0026E1F0(s32 arg0, s32 arg1);
s32 strcmp(void *arg0, void *arg1);

void func_00270DE8(s32 arg0, s32 arg1, s32 arg2) {
    u8 *s0;
    u8 *s2;
    s32 s1;
    u32 s3;
    u32 cnt;
    u32 cond;

    s2 = (u8 *)(*(s32 *)arg0 + *(s32 *)arg1 * 0xC0);
    func_0026E1F0((s32)(s2 + 0xA8), arg2);
    s1 = *(s32 *)(arg1 + 4);
    s3 = 1;
    if (s1 != 0) {
        s0 = s2 + 0xC0;
        for (;;) {
            cnt = (u32)(*(s32 *)(arg0 + 4) - *(s32 *)arg1);
            cond = s3 < cnt;
            s3 += 1;
            if (!cond) {
                break;
            }
            if (strcmp((void *)s0, (void *)s2) != 0) {
                s0 += 0xC0;
                continue;
            }
            s1 -= 1;
            func_0026E1F0((s32)(s0 + 0xA8), arg2);
            s0 += 0xC0;
            if (s1 == 0) {
                break;
            }
        }
    }
}
