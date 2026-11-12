#include "common.h"

void func_002C0F30(s32 arg0, s32 arg1, s32 arg2);
s64 func_002C10E8(s64 arg0, u64 arg1);

void func_002C5070(u8 *arg0) {
    s32 sp[2];

    if (*(s32 *)(arg0 + 0x1324) != 0) {
        func_002C0F30(*(s32 *)(arg0 + 0x1324), (s32)&sp[0], (s32)&sp[1]);
        *(s64 *)(arg0 + 0x988) = func_002C10E8(*(s64 *)(arg0 + 0x988), sp[0]);
    }
}
