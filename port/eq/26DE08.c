#include "common.h"

void *func_0028BAA8(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

s32 func_0026DE08(s32 arg0, u8 *arg1, u8 *arg2) {
    void *temp_v0;

    memset(arg1, 0, 0x18);
    *(s32 *)(arg1 + 0) = arg0;
    *(s32 *)(arg1 + 4) = (s32)(arg2 + 2);
    *(u8 *)(arg1 + 0x12) = arg2[0];
    *(u8 *)(arg1 + 0x13) = arg2[1];
    temp_v0 = func_0028BAA8((*(u16 *)(arg1 + 0x12)) * 0xC);
    *(s32 *)(arg1 + 0x14) = (s32)temp_v0;
    memset(temp_v0, 0, (*(u16 *)(arg1 + 0x12)) * 0xC);
    return (*(u16 *)(arg1 + 0x12)) * 0xC;
}
