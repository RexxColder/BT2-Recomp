#include "common.h"

void func_002D2E38(s32 arg0, s32 arg1, s32 arg2);
void func_002D2EF8(s32 arg0, s32 arg1, s32 arg2);

void func_002D2D78(s32 arg0, u8 *arg1) {
    func_002D2EF8(arg0, 2, 3);
    func_002D2E38(arg0, 3, 4);
    if (*(s32 *)(arg1 + 0x14) != 0) {
        func_002D2EF8(arg0, 4, 5);
        func_002D2E38(arg0, 5, 6);
        func_002D2EF8(arg0, 6, 7);
        return;
    }
    func_002D2EF8(arg0, 4, 7);
}
