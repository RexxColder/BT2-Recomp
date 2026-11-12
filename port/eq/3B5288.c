#include "m2c_macros.h"

void func_3126C8(void *, s32);

void func_003B5288(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 != 0) {
        func_3126C8((u8 *)arg0 + 0x160, arg1);
        func_3126C8((u8 *)arg0 + 0x170, arg2);
        func_3126C8((u8 *)arg0 + 0x180, arg3);
        func_3126C8((u8 *)arg0 + 0x190, arg4);
    }
}
