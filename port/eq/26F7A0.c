#include "common.h"

u8 *func_0026F198(u8 *arg0);
void func_0026FBD0(s32 arg0);
void Flash_CxformIdentity(s32 arg0);
extern void *memcpy(void *dst, const void *src, u32 n);

/* 0x0026F7A0: new object from func_0026F198(arg0) (0 -> return 0): word0 = 1, word1 = arg1, bytes +8..+0x1F from arg2
 * (or func_0026FBD0 when arg2 is null), +0x20..+0x37 from arg3 (or Flash_CxformIdentity). Returns the object. */
u8 *func_0026F7A0(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3) {
    u8 *s0;

    s0 = func_0026F198(arg0);
    if (s0 == 0) {
        return 0;
    }
    *(s32 *)s0 = 1;
    *(s32 *)(s0 + 4) = arg1;
    if (arg2 == 0) {
        func_0026FBD0((s32)(s0 + 8));
    } else {
        memcpy(s0 + 8, arg2, 0x18);
    }
    if (arg3 == 0) {
        Flash_CxformIdentity((s32)(s0 + 0x20));
    } else {
        memcpy(s0 + 0x20, arg3, 0x18);
    }
    return s0;
}
