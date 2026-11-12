#include "common.h"

void func_002F9300(u8 *arg0);
void func_002F9C80(u8 *arg0);
s32 strlen(s8 *arg0);
s32 strncmp(s8 *arg0, s8 *arg1, s32 arg2);
extern u8 D_0037D5D0[] __attribute__((section(".data")));
extern u8 D_0037D5F8[] __attribute__((section(".data")));
extern u8 D_0039D93C[] __attribute__((section(".data")));

s32 func_002FA318(s8 *arg0) {
    s8 buf[0x130];
    s32 s1;
    s32 s2;
    s32 s4;
    s32 off;
    u8 *fp;
    s32 (*fn)(u8 *);

    s4 = 0;
    if (arg0 == NULL || *arg0 == 0) {
        func_002F9C80((u8 *)buf);
        if (buf[0] == 0) {
            func_002F9300(D_0037D5D0);
            return 0;
        }
    } else {
        memcpy(buf, arg0, strlen(arg0) + 1);
    }

    s2 = strlen(buf);
    if (s2 <= 0) {
        func_002F9300(D_0037D5D0);
        return 0;
    }

    s1 = 0;
    off = 0;
    for (;;) {
        s1 += 1;
        if (strncmp(buf, (s8 *)(D_0039D93C + off), s2) == 0) {
            fp = *(u8 **)(D_0039D93C + off - 4);
            if (fp == NULL) {
                func_002F9300(D_0037D5F8);
                return 0;
            }
            fn = *(s32 (**)(u8 *))(fp + 0xC);
            if (fn != NULL) {
                s4 = fn(D_0037D5F8);
            }
        }
        off = s1 * 0x10;
        if (s1 >= 0x20) {
            return s4;
        }
    }
}
