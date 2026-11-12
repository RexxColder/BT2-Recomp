#include "common.h"

void func_002DCA68(s32 arg0, s32 arg1);
s32 func_002DCC38(s32 arg0);

void func_002DC680(s32 arg0, s32 arg1) {
    if (func_002DCC38(arg0) != 0) {
        func_002DCA68(0, (s32)0xFF020201);
        return;
    }
    *(s64 *)arg1 = *(s64 *)((u8 *)arg0 + 0x18);
    *(s64 *)((u8 *)arg1 + 8) = *(s64 *)((u8 *)arg0 + 0x20);
}
