#include "common.h"

void func_002D5F18(s32 arg0, s32 arg1);
void func_002D6C90(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D7B30(s32 arg0);
void func_002D8068(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037AA88[] __attribute__((section(".data")));

void func_002D6090(s32 arg0, s32 arg1) {
    if (func_002D7B30(*(s32 *)(arg0 + 0x24)) != 1) {
        func_002D6C90(arg0, arg1, (s32)D_0037AA88);
        return;
    }
    func_002D8068(arg0, 0x10, (s32)D_0037AA88);
    func_002D5F18(arg0, arg1);
}
