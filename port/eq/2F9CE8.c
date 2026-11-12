#include "common.h"

void func_002F9300(s32 arg0);
void func_002F9B28(s32 arg0);
extern u8 D_0037D2A8[] __attribute__((section(".data")));
extern u8 D_0037D2C8[] __attribute__((section(".data")));

/* 0x002F9CE8(obj): NULL gives func_002F9300(&D_0037D2A8). Otherwise f = the method at (*obj)+0x14: when f == 0,
 * func_002F9300(&D_0037D2C8); else f(*(obj+4)) and tail-call func_002F9B28(obj). */
void func_002F9CE8(u8 *arg0) {
    s32 f;

    if (arg0 == 0) {
        func_002F9300((s32)D_0037D2A8);
        return;
    }
    f = *(s32 *)(*(s32 *)arg0 + 0x14);
    if (f == 0) {
        func_002F9300((s32)D_0037D2C8);
        return;
    }
    ((void (*)(s32))f)(*(s32 *)(arg0 + 4));
    func_002F9B28((s32)arg0);
}
