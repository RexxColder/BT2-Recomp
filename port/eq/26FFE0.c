#include "common.h"

s32 func_0026FC38(s32 arg0, s32 arg1);
void func_0026FBD0(s32 arg0);
void Flash_CxformIdentity(s32 arg0);
void *memcpy(void *dst, const void *src, u32 n);
void *memset(void *dst, s32 c, u32 n);
u32 strlen(const char *s);

/* 0x0026FFE0: allocate and set up an entry from a name (arg2), with two optional 24-byte blocks (arg3, arg4)
 * copied into +0x78 and +0x90 (defaults when null). Returns the entry, or 0 when the allocation fails. */
s32 func_0026FFE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *s0;

    s0 = (u8 *)func_0026FC38(arg0, arg1);
    if (s0 == NULL) {
        return 0;
    }
    memset(s0, 0, 0x40);
    memcpy(s0, (const void *)arg2, strlen((const char *)arg2));
    *(s32 *)(s0 + 0x44) = *(s32 *)(s0 + 0x44) | 3;
    memset(s0 + 0x48, 0, 0x60);
    *(f32 *)(s0 + 0x54) = 1.0f;

    if (arg3 != 0) {
        memcpy(s0 + 0x78, (const void *)arg3, 24);
    } else {
        func_0026FBD0((s32)(s0 + 0x78));
    }

    if (arg4 != 0) {
        memcpy(s0 + 0x90, (const void *)arg4, 24);
    } else {
        Flash_CxformIdentity((s32)(s0 + 0x90));
    }

    s0[0xB9] = s0[0xB9] | 2;
    return (s32)s0;
}
