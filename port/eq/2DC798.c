#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002DCC38(u8 *arg0);
void func_002DCA68(s32 arg0, s32 arg1);

/* 0x002DC798(obj, out): when func_002DCC38(obj) is nonzero: tail-call func_002DCA68(0, 0xFF020202); otherwise copy
 * the 32 bytes at obj+0x28 to out. */
void func_002DC798(u8 *arg0, u8 *arg1) {
    if (func_002DCC38(arg0) != 0) {
        func_002DCA68(0, 0xFF020202);
        return;
    }
    memcpy(arg1, arg0 + 0x28, 0x20);
}
