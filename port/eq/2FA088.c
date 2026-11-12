#include "common.h"

void func_002F9300(void *a0);
void func_002F9B38(void *a0, void *a1, s32 a2);
void *func_002F98F0(void *a0, void *a1, s32 a2);
extern u8 D_0037D440 __attribute__((section(".data")));
extern u8 D_0037D490 __attribute__((section(".data")));
extern u8 D_0037D4B8 __attribute__((section(".data")));

s32 cvFsGetFileSize(s32 arg0) {
    u8 buf[0x260];   /* tamano de locales del original (antes 0x140) */
    u8 *s1;
    u8 *s0;
    s32 (*fp)(void *);

    s1 = buf + 0x130;
    if (arg0 == 0) {
        func_002F9300(&D_0037D440);
        return 0;
    }
    func_002F9B38(buf, s1, arg0);
    if (*(s8 *)s1 == 0) {
        func_002F9300(&D_0037D440);
        return 0;
    }
    s0 = (u8 *)func_002F98F0(buf, s1, arg0);
    if (s0 == NULL) {
        func_002F9300(&D_0037D490);
    }
    fp = *(s32 (**)(void *))(s0 + 8);
    if (fp == NULL) {
        func_002F9300(&D_0037D4B8);
        return 0;
    }
    return fp(s1);
}
