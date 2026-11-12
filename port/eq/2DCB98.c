#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002DCC38(u8 *arg0);
s32 func_002DCA68(s32 arg0, s32 arg1);
extern u8 *D_00347600;

/* 0x002DCB98(obj, out): obj == NULL: copy 12 bytes of D_00347600 to out. Else when func_002DCC38(obj) is zero copy
 * 12 bytes from obj+4 to out; otherwise tail-call func_002DCA68(0, 0xFF020102), which returns that code. */
s32 func_002DCB98(u8 *arg0, u8 *arg1) {
    if (arg0 == NULL) {
        memcpy(arg1, D_00347600, 12);
        return 0;
    }
    if (func_002DCC38(arg0) == 0) {
        memcpy(arg1, arg0 + 4, 12);
        return 0;
    }
    return func_002DCA68(0, 0xFF020102);
}
