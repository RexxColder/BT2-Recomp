#include "common.h"

void func_002B2DF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002B2F48(s32 arg0);
extern s32 D_00345338 __attribute__((section(".data")));

void func_002B2E48(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 buf[4];
    s32 s1;
    s32 v0;
    s32 sp0;
    s32 sp4;
    s32 a;
    s32 b;
    s32 tmp;
    s32 var;
    u32 t9;

    if (D_00345338 != 0) {
        *arg1 = 0;
        *arg2 = 0;
        return;
    }
    s1 = *(s32 *)(arg0 + 0x10);
    func_002B2DF8(arg0, (s32)&buf[0], (s32)&buf[1], (s32)&buf[2], (s32)&buf[3]);
    v0 = func_002B2F48(*(s32 *)(arg0 + 0x24));
    sp0 = buf[0];
    sp4 = buf[1];
    t9 = (u32)sp0 * (u32)sp4 * 9u;
    a = (sp0 < 0) ? (sp0 + 15) : sp0;
    a = a >> 4;
    b = (sp4 < 0) ? (sp4 + 15) : sp4;
    b = b >> 4;
    tmp = a * b;
    *arg1 = ((s32)(t9 + (t9 >> 31)) >> 1) + 0x86910;
    var = s1 * ((tmp << 10) + 0x40);
    if (v0 != 2) {
        var = s1 * ((tmp * 0x180) + 0x40);
    }
    *arg2 = var;
}
