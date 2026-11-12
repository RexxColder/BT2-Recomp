#include "common.h"

s32 func_002B95F8(u8 *arg0, s32 arg1);

s32 func_002B5CB8(u8 *arg0) {
    s32 r = func_002B95F8(arg0, *(s32 *)(arg0 + 0xB8));
    if (r == 0x51 || r == 0x61) {
        return 0x41;
    }
    return r;
}
