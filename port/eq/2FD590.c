#include "common.h"

s32 func_002FC550(s32 arg0);
s32 func_002FD318(s32 arg0, s32 arg1);
void func_002FDF58(s32 arg0, s32 arg1);
s32 func_002FE7C8(s32 arg0, s32 arg1);
s32 sceCdSync(s32 arg0);
extern u8 D_00356BC0[] __attribute__((section(".data")));

s32 func_002FD590(s32 arg0) {
    s32 sp[12];
    s32 v0;

    if (arg0 == 0) {
        return 0;
    }
    func_002FE7C8(arg0, (s32)sp);
    if (sp[1] != 0) {
        return 1;
    }
    func_002FDF58(arg0, (s32)D_00356BC0);
    func_002FC550(0x8100);
    sceCdSync(0);
    func_002FC550(0x8101);
    v0 = func_002FD318((s32)sp, (s32)D_00356BC0);
    if (v0 != 0) {
        return 1;
    }
    return 0;
}
