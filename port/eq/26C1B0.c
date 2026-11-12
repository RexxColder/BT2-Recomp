#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);

void *func_0026C1B0(u8 *arg0) {
    s32 saved = *(s32 *)arg0;
    void *ret = memset(arg0, 0, 0x44);
    *(s32 *)arg0 = saved;
    return ret;
}
