#include "m2c_macros.h"

void func_3126C8(void *, s32);

void func_003B5158(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0 != 0) {
        func_3126C8((u8 *)arg0 + 0xE0, arg1);
        func_3126C8((u8 *)arg0 + 0xF0, arg2);
        func_3126C8((u8 *)arg0 + 0x100, arg3);
        func_3126C8((u8 *)arg0 + 0x110, arg4);
    }
}
