#include "common.h"

void func_002C8078(s32 arg0, s32 arg1);
void func_002D1C18(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002C6F80(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 buf[8];
    s32 out1;
    s32 out2;
    s32 ret = 0;

    if (*(s32 *)(arg0 + 0xD98) != 0) {
        func_002C8078((s32)(arg0 + 0xD9C), (s32)buf);
        buf[6] = 0;
        func_002D1C18((s32)buf, (s32)&out1, (s32)&out2, arg3);
        ret = out1 - *(s32 *)(arg0 + 0xD6C + 0x24);
    }
    return ret;
}
