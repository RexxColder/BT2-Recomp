#include "common.h"

extern u8 *D_00387E04;

void *memcpy(void *arg0, const void *arg1, u32 arg2);
u8 *Queue_Push(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 Queue_Count(u8 *arg0);

s32 func_002A86E8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *s3;

    s3 = Queue_Push(D_00387E04 + 0xA0, 0, arg2, arg3);
    memcpy(s3, arg0, 0x20);
    *(s32 *)(s3 + 0x20) = arg1;
    *(s32 *)(s3 + 0x24) = arg2;
    if (Queue_Count(D_00387E04 + 0xA0) == 1) {
        ((void (*)(u8 *))(long)(*(s32 *)(s3 + 0x20)))(s3);
        return 1;
    }
    return 0;
}
