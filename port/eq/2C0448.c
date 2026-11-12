#include "common.h"

s32 func_002C0448(void **arg0, s32 arg1, void *arg2, void *arg3) {
    s32 temp_s4;

    temp_s4 = ((s32 (*)(void *, s32, void *, void *))(*(void **)((u8 *)*arg0 + 0x24)))(arg0, arg1, arg2, arg3);
    ((void (*)(void *, s32, s32, void *))(*(void **)((u8 *)*arg0 + 0x18)))(arg0, arg1, 0x7FFFFFFF, arg2);
    if (*(s32 *)((u8 *)arg2 + 4) < temp_s4) {
        ((void (*)(void *, s32, s32, void *))(*(void **)((u8 *)*arg0 + 0x18)))(arg0, arg1, 0x7FFFFFFF, arg3);
        ((void (*)(void *, s32, void *))(*(void **)((u8 *)*arg0 + 0x1C)))(arg0, arg1, arg3);
    } else {
        *(s32 *)((u8 *)arg3 + 4) = 0;
        *(s32 *)((u8 *)arg3 + 0) = 0;
    }
    ((void (*)(void *, s32, void *))(*(void **)((u8 *)*arg0 + 0x1C)))(arg0, arg1, arg2);
    return temp_s4;
}
