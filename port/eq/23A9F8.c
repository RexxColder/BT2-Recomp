#include "common.h"

extern s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_0023A9F8(s32 arg0) {
    func_002113C0(arg0, 0xC, 0x20, 0);
    func_002113C0(arg0, 0xC, 0x40, 0);
    func_002113C0(arg0, 0xC, 0x80, 0);
    func_002113C0(arg0, 0xC, 0x100, 0);
    func_002113C0(arg0, 0xC, 0x200, 0);
    func_002113C0(arg0, 0xC, 0x400, 0);
    return func_002113C0(arg0, 0xC, 0x800, 0);
}
