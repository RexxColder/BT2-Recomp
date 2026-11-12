#include "common.h"

void *memset(void *arg0, s32 arg1, s32 arg2);
s32 vsprintf(u8 *arg0, const char *arg1, __builtin_va_list arg2);
void func_002BC630(u8 *arg0);
extern u8 D_00393D40[] __attribute__((section(".data")));

/* 0x002BC568 Rand_Range(fmt, ...) (the asm label; a printf-style log helper): clear the 256-byte buffer
 * D_00393D40, vsprintf the format and its varargs into it, and pass the buffer to func_002BC630. */
void Rand_Range(const char *arg0, ...) {
    __builtin_va_list ap;

    memset(D_00393D40, 0, 0x100);
    __builtin_va_start(ap, arg0);
    vsprintf(D_00393D40, arg0, ap);
    __builtin_va_end(ap);
    func_002BC630(D_00393D40);
}
