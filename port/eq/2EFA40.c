#include "common.h"

s32 vsprintf(char *arg0, const char *arg1, __builtin_va_list arg2);
void func_00331710(char *arg0);
extern s32 D_003534A0 __attribute__((section(".data")));

/* 0x002EFA40(fmt, ...): unless D_003534A0 != 0, formats fmt and the varargs into a 0x98-byte buffer with vsprintf
 * and passes the buffer to func_00331710. */
void func_002EFA40(const char *arg0, ...) {
    char buf[0x98];
    __builtin_va_list ap;

    if (D_003534A0 != 0) {
        return;
    }
    __builtin_va_start(ap, arg0);
    vsprintf(buf, arg0, ap);
    __builtin_va_end(ap);
    func_00331710(buf);
}
