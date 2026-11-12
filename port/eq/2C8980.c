#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);
void func_002DE2B0(s32 arg0, s32 arg1, s32 arg2);

void func_002C8980(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[2];
    s32 s0;
    s32 s3;
    s32 r;

    s3 = *(s32 *)(arg0 + 0x1FC0);
    s0 = *(s32 *)(s3 + 0x74);
    if (*(s32 *)(s3 + 0x110) != 0) {
        func_002DE2B0(*(s32 *)(s3 + 0), (s32)&sp[0], (s32)&sp[1]);
        if (sp[0] != 1) {
            if (*(s32 *)(arg0 + 0xE48) == 0) {
                r = func_002D07B0(arg0, 0x49);
                if ((r ^ 1) == 0) {
                    sp[1] = r;
                }
            }
            if ((sp[1] ^ 1) == 0) {
                s0 = 2;
            }
        } else {
            s0 = 5;
        }
    }
    if (arg2 == 1) {
        if ((u32)(*(s32 *)(arg1 + 0x18) - 1) < 2U) {
            s0 = 2;
        }
    } else if (s0 == 2) {
        s0 = 3;
    } else if ((s0 ^ 3) == 0) {
        s0 = 5;
    }
    *(s32 *)(s3 + 0x74) = s0;
}
