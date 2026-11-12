#include "common.h"

void func_002D5D08(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D8008(s32 arg0, s32 arg1, s32 arg2);

void func_002D7F08(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_002D8008(arg2, *(s32 *)(arg1 + 4), *(s32 *)(arg0 + 0xC));
    if (arg2 != 0x10 && arg2 == 0x20) {
        func_002D5D08(arg0, arg1, 0xD);
    }
}
