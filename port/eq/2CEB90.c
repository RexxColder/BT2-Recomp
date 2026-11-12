#include "common.h"

s32 func_002C3210(u8 *arg0);
void func_002C2FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002D2FC8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_002CEB90(u8 *arg0) {
    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(0, 0xFF00013C, 5, 0, 0);
        return;
    }
    *(s32 *)(arg0 + 0x60) = 1;
    func_002D2FC8(arg0, 1, 5, 0, 0);
    func_002D2FC8(arg0, 2, 5, 0, 0);
    func_002D2FC8(arg0, 3, 5, 0, 0);
}
