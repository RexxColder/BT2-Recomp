#include "common.h"

s32 atoi(s32 arg0);
s32 func_002DCE50(s32 arg0);
s32 strncmp(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037AFD0[] __attribute__((section(".data")));
extern u8 D_0037AFD8[] __attribute__((section(".data")));

s32 func_002DFA00(u8 *arg0, s32 arg1, s32 arg2) {
    s32 s0;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 v1;

    s3 = arg2 - 4;
    s2 = 0;
    s4 = arg1 + 4;
    if (s3 > 0) {
        s0 = s4;
        do {
            s2 += 1;
            if (strncmp(s0, (s32)D_0037AFD0, 7) == 0) {
                *(s32 *)(arg0 + 0x398) = (atoi(s0 + 0x10) != 0) ? 3 : 0;
            }
            if (strncmp(s0, (s32)D_0037AFD8, 7) == 0) {
                *(s32 *)(arg0 + 0x360) = atoi(s0 + 0x10);
                *(s32 *)(arg0 + 0x364) = atoi(s0 + 0x18);
                *(s32 *)(arg0 + 0x368) = atoi(s0 + 0x20);
            }
            if (func_002DCE50(s0) != 0) {
                break;
            }
            s0 = s4 + s2;
        } while (s2 < s3);
    }
    v1 = *(s32 *)(arg0 + 0x360);
    return ((v1 == 8) || (v1 == 9)) ? -1 : 0;
}
