#include "common.h"

s32 func_0012D970(u8 *arg0) {
    s32 sum = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        u8 *p = arg0 + i * 0x10;
        s32 flag = 1;

        if (*(s32 *)(p + 8) > 0) {
            s32 a = *(s32 *)(p + 0);

            if (a > 0xFFEF) {
            } else if (a > 0) {
                s32 b = *(s32 *)(p + 4);

                if (!(b > 0xFFEF)) {
                    flag = (b < 1);
                }
            }
        }
        sum += flag;
    }
    return sum > 0;
}
