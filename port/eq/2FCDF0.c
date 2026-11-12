#include "common.h"

void func_002FCB38(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002FD258(s32 arg0);
s32 memset(s32 arg0, s32 arg1, s32 arg2);

void func_002FCDF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    *(s8 *)((u8 *)arg0 + 2) = 0;
    if (*(s8 *)((u8 *)arg0 + 1) == 1) {
        do {
            func_002FD258(arg0);
        } while (*(s8 *)((u8 *)arg0 + 1) == 1);
    }
    func_002FCB38(*(s32 *)((u8 *)arg0 + 4), arg1, arg2, arg3);
    memset(arg0, 0, 0x44);
}
