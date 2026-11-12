#include "common.h"

void func_002DCA68(s32 arg0, s32 arg1);
s32 func_002DCC38(s32 arg0, s32 arg1);

void func_002DC830(s32 arg0, s32 arg1) {
    if (func_002DCC38(arg0, arg1) != 0) {
        func_002DCA68(0, 0xFF020203);
        return;
    }
    *(s64 *)(arg1 + 0x00) = *(s64 *)(arg0 + 0xA8);
    *(s64 *)(arg1 + 0x08) = *(s64 *)(arg0 + 0xB0);
    *(s64 *)(arg1 + 0x10) = *(s64 *)(arg0 + 0xB8);
    *(s64 *)(arg1 + 0x18) = *(s64 *)(arg0 + 0xC0);
    *(s64 *)(arg1 + 0x20) = *(s64 *)(arg0 + 0xC8);
}
