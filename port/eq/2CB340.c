#include "common.h"

s32 DIntr(void);
void func_003382B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002CB340(s32 arg0) {
    DIntr();
    *(s32 *)0x1000F590 = *(s32 *)0x1000F520 | 0x10000;
    *(s32 *)0x1000B400 = arg0;
    *(s32 *)0x1000F590 = *(s32 *)0x1000F520 & 0xFFFEFFFF;
    func_003382B8(0x1000B400, 0x1000F520, 0x1000F590, 0x10000);
}
