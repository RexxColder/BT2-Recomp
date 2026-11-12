#include "common.h"

void func_001C2158(u8 *arg0, s32 arg1);
void func_00129AB0(u8 *arg0);

void func_001C2298(u8 *arg0) {
    __builtin_memset(arg0, 0, 0xF0);
    func_001C2158(arg0, 2);
    func_00129AB0(arg0 + 0xE0);
}
