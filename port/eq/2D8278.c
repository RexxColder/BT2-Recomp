#include "common.h"

s32 atoi(char *s);

s32 func_002D8278(u8 *arg0, s32 arg1) {
    char buf[4];

    if (arg0 == NULL || arg1 < 0) {
        return 0;
    }
    buf[0] = *(s8 *)(arg0 + 0x10);
    buf[1] = *(s8 *)(arg0 + 0x11);
    buf[2] = 0;
    buf[3] = 0;
    return atoi(buf);
}
