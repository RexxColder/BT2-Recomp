#include "common.h"

s64 __divdi3(s64 arg0, s64 arg1);
s64 __muldi3(s64 arg0, s64 arg1);

void func_002D3240(void *arg0, void *arg1) {
    s64 temp;

    if (*(s32 *)((u8 *)arg0 + 0xC) == 0) {
        temp = __muldi3(*(s64 *)((u8 *)arg0 + 0x130), *(s64 *)arg1);
        temp = __divdi3(temp, *(s64 *)((u8 *)arg1 + 0x8));
        *(s64 *)((u8 *)arg0 + 0x128) = *(s64 *)((u8 *)arg0 + 0x128) + temp;
    }
}
