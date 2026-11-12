#include "common.h"

extern s32 func_002D07B0(s32 arg0, s32 arg1);
extern void func_002DA838(s32 arg0, s32 arg1, s32 arg2);

void func_002C35E0(u8 *self) {
    s32 first = *(s32 *)*(u8 **)(self + 0x1F7C);
    s32 second = func_002D07B0((s32)self, 0x55);
    s32 third = func_002D07B0((s32)self, 0x56);

    func_002DA838(first, second, third);
}
