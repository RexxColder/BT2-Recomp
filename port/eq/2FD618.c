#include "common.h"

void func_002FE7C8(s32 arg0, s32 arg1);
s32 func_002FD318(s32 arg0, s32 arg1);
void func_002FDF58(s32 arg0, s32 arg1);
void func_002FC550(s32 arg0);
void sceCdSync(s32 arg0);
void func_002EFAB8(s32 arg0, s32 arg1);
void func_002FD2E8(s32 arg0, s32 arg1);
extern u8 D_00356BC0[] __attribute__((section(".data")));
extern u8 D_0037E2C8[] __attribute__((section(".data")));
extern u8 D_0037E2F8[] __attribute__((section(".data")));
extern u8 D_0037E320[] __attribute__((section(".data")));

s32 func_002FD618(s32 arg0) {
    s32 sp[12];
    u8 *var_a1;
    s32 var_a0;

    var_a0 = arg0;
    if (var_a0 == 0) {
        var_a1 = D_0037E2C8;
        func_002FD2E8(var_a0, (s32)var_a1);
        return 0;
    }
    func_002FE7C8(arg0, (s32)sp);
    if (sp[1] == 0) {
        func_002FDF58(var_a0, (s32)D_00356BC0);
        func_002FC550(0x8200);
        sceCdSync(0);
        func_002FC550(0x8201);
        if (func_002FD318((s32)sp, (s32)D_00356BC0) == 0) {
            func_002EFAB8((s32)D_0037E2F8, (s32)D_00356BC0);
            var_a1 = D_0037E320;
            var_a0 = 0;
            func_002FD2E8(var_a0, (s32)var_a1);
            return 0;
        }
        return sp[1];
    }
    return sp[1];
}
