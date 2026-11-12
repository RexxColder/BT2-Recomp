#include "common.h"

s32 func_002C3210(void *arg0);
void func_002C2FF0(s32 arg0, s32 arg1);
void func_002CE6D8(void *arg0, s32 arg1);

void func_002CE680(void *arg0) {
    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(0, 0xFF000133);
        return;
    }
    func_002CE6D8(arg0, 0xFF000133);
    *(s32 *)((u8 *)arg0 + 0x44) = 1;
}
