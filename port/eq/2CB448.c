#include "common.h"

void func_002CB340(s32 arg0, s32 arg1, s32 arg2);
void func_002CB3A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002CB448(u8 *arg0) {
    s32 i;
    s32 n;
    s32 base4;
    s32 tmp;
    u8 *p;

    *(s32 *)(arg0 + 0x44) = 1;
    *(s32 *)(arg0 + 0xC) = 0;
    *(s32 *)(arg0 + 0x10) = 0;
    *(s32 *)(arg0 + 0x14) = 0;
    *(s32 *)(arg0 + 0x58) = 0;
    *(s32 *)(arg0 + 0x5C) = 0;
    n = *(s32 *)(arg0 + 0x54);
    if (n > 0) {
        p = *(u8 **)(arg0 + 0x50);
        i = 0;
        do {
            *(s32 *)(p + 0x10) = 0;
            i += 1;
            *(s32 *)(p + 0x14) = 0;
            *(s64 *)(p + 0) = -1;
            *(s64 *)(p + 8) = -1;
            p += 0x18;
        } while (i < *(s32 *)(arg0 + 0x54));
    }
    i = 0;
    if (*(s32 *)(arg0 + 8) > 0) {
        do {
            base4 = *(s32 *)(arg0 + 4);
            tmp = ((i << 11) + *(s32 *)(arg0 + 0)) & 0x0FFFFFFF;
            func_002CB3A8(base4 + i * 0x10, tmp, 3, 0x80);
            i += 1;
        } while (i < *(s32 *)(arg0 + 8));
    }
    base4 = *(s32 *)(arg0 + 4);
    func_002CB3A8(base4 + i * 0x10, base4 & 0x0FFFFFFF, 2, 0);
    tmp = *(s32 *)(arg0 + 4) & 0x0FFFFFFF;
    *(s32 *)0x1000B420 = 0;
    *(s32 *)0x1000B410 = *(s32 *)(arg0 + 0) & 0x0FFFFFFF;
    *(s32 *)0x1000B430 = tmp;
    func_002CB340(5, 0x1000B430, tmp);
    return 1;
}
