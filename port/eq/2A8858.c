#include "common.h"

void *func_0028BAA8(s32 arg0);
void *memset(void *arg0, s32 arg1, s32 arg2);

void func_002A8858(void *arg0, s32 arg1) {
    void *temp_v0;

    memset(arg0, 0, 0x14);
    *(s32 *)arg0 = arg1;
    temp_v0 = func_0028BAA8(arg1 * 8);
    *(void **)((u8 *)arg0 + 0x4) = temp_v0;
    memset(temp_v0, 0, *(s32 *)arg0 * 8);
}
