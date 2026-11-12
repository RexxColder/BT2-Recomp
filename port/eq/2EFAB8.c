#include "common.h"

s32 vsprintf(char *arg0, const char *arg1, __builtin_va_list arg2);
void func_00331710(char *arg0);
extern s32 D_003534A0 __attribute__((section(".data")));

/* 0x002EFAB8: same body as func_002EF9C0 (printf-style log helper, skipped when D_003534A0 == 2). */
void func_002EFAB8(const char *arg0, ...) {
    char buf[0x98];
    __builtin_va_list ap;

    if (D_003534A0 == 2) {
        return;
    }
    __builtin_va_start(ap, arg0);
    vsprintf(buf, arg0, ap);
    __builtin_va_end(ap);
    func_00331710(buf);
}
